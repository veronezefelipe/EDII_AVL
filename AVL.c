#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
    int dado;
    int altura;
    struct sNodo* esq;
    struct sNodo* dir;
} NodoAVL;

typedef struct {
    struct sNodo* raiz;
} AVLTree;

NodoAVL* criaNodo(int dado) {
    NodoAVL* nodo = (NodoAVL*)malloc(sizeof(NodoAVL));
    if (nodo != NULL) {
        nodo->dado = dado;
        nodo->altura = 1;
        nodo->esq = NULL;
        nodo->dir = NULL;
    }
    return nodo;
}

int altura(NodoAVL* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int calculaBalanceamento(NodoAVL* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->esq) - altura(nodo->dir);
}

NodoAVL* rotacaoDireita(NodoAVL* y) {
    NodoAVL* x = y->esq;
    NodoAVL* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NodoAVL* rotacaoEsquerda(NodoAVL* x) {
    NodoAVL* y = x->dir;
    NodoAVL* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

NodoAVL* inserir(NodoAVL* nodo, int dado) {
    if (nodo == NULL) {
        return criaNodo(dado);
    }

    if (dado < nodo->dado) {
        nodo->esq = inserir(nodo->esq, dado);
    } else if (dado > nodo->dado) {
        nodo->dir = inserir(nodo->dir, dado);
    } else {
        // Dados iguais não são permitidos em uma árvore de busca binária.
        return nodo;
    }

    nodo->altura = 1 + max(altura(nodo->esq), altura(nodo->dir));

    int balanceamento = calculaBalanceamento(nodo);

    // Casos de desbalanceamento
    // Rotação à direita simples
    if (balanceamento > 1 && dado < nodo->esq->dado) {
        return rotacaoDireita(nodo);
    }

    // Rotação à esquerda simples
    if (balanceamento < -1 && dado > nodo->dir->dado) {
        return rotacaoEsquerda(nodo);
    }

    // Rotação à esquerda e, em seguida, à direita
    if (balanceamento > 1 && dado > nodo->esq->dado) {
        nodo->esq = rotacaoEsquerda(nodo->esq);
        return rotacaoDireita(nodo);
    }

    // Rotação à direita e, em seguida, à esquerda
    if (balanceamento < -1 && dado < nodo->dir->dado) {
        nodo->dir = rotacaoDireita(nodo->dir);
        return rotacaoEsquerda(nodo);
    }

    return nodo;
}

void insereNaAVL(AVLTree* avl, int valor) {
    if (avl != NULL) {
        avl->raiz = inserir(avl->raiz, valor);
    }
}

void emOrdem(NodoAVL* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%i, ", raiz->dado);
        emOrdem(raiz->dir);
    }
}

int main() {
    AVLTree* avl = (AVLTree*)malloc(sizeof(AVLTree));
    avl->raiz = NULL;

    insereNaAVL(avl, 12);
    insereNaAVL(avl, 15);
    insereNaAVL(avl, 14);
    insereNaAVL(avl, 16);
    insereNaAVL(avl, 10);
    insereNaAVL(avl, 9);
    insereNaAVL(avl, 12);
    insereNaAVL(avl, 13);
    insereNaAVL(avl, 11);
    insereNaAVL(avl, 8);

    printf("Valores na AVL em ordem:\n");
    emOrdem(avl->raiz);
    printf("\n");

    free(avl);  // Liberar a memória alocada para a árvore

    return 0;
}
