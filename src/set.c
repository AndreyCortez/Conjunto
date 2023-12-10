#include "set.h"
#include <stdio.h>
#include <stdlib.h>

struct set {
    AVL *conjunto;
};

SET *set_criar(void) {
    SET *novo_conjunto = (SET *)malloc(sizeof(SET));
    if (novo_conjunto != NULL)
        novo_conjunto->conjunto = avl_criar();  // Inicializar a árvore AVL
    return novo_conjunto;
}

bool set_pertence(SET *A, int elemento) {
    if (A == NULL)
        return false;
    return avl_buscar(A->conjunto, elemento) != NULL;
}

bool set_inserir(SET *s, int elemento) {
    if (s == NULL)
        return false;
    return avl_inserir(s->conjunto, elemento);
}

bool set_remover(SET *s, int elemento) {
    if (s == NULL)
        return false;
    return avl_remover(s->conjunto, elemento);
}

void set_apagar(SET **s) {
    if (*s != NULL) {
        avl_apagar(&(*s)->conjunto);
        free(*s);
        *s = NULL;
    }
}

void set_imprimir(SET *s) {
    if (s != NULL)
        avl_imprimir(s->conjunto);
}

SET *set_uniao(SET *A, SET *B) {
    if (A == NULL)
        return B;
    if (B == NULL)
        return A;

    SET *uniao = set_criar();
    uniao->conjunto = avl_uniao(A->conjunto, B->conjunto);

    return uniao;
}
SET *set_interseccao(SET *A, SET *B){
    if (A == NULL || B == NULL)
        return NULL;

    SET *intersecao = set_criar();

    intersecao->conjunto = avl_interseccao(A->conjunto, B->conjunto);

    return intersecao;
}