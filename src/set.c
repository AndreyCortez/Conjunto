#include "set.h"
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do conjunto
struct set {
    AVL *conjunto;  // Árvore AVL que representa o conjunto
};

// Função para criar um novo conjunto
SET *set_criar(void) {
    SET *novo_conjunto = (SET *)malloc(sizeof(SET));
    if (novo_conjunto != NULL)
        novo_conjunto->conjunto = avl_criar();  // Inicializar a árvore AVL
    return novo_conjunto;
}

// Função para poder setar o conjunto de um set
bool set_set_conjunto(SET* s, AVL* conjunto)
{
    if (s == NULL || conjunto == NULL)
        return false;
    avl_apagar(&s->conjunto);
    s->conjunto = conjunto;
    return true;
}

// Função para verificar se um elemento pertence ao conjunto
bool set_pertence(SET *A, int elemento) {
    if (A == NULL)
        return false;
    return avl_buscar(A->conjunto, elemento) != NULL;
}

// Função para inserir um elemento no conjunto
bool set_inserir(SET *s, int elemento) {
    if (s == NULL)
        return false;
    return avl_inserir(s->conjunto, elemento);
}

// Função para remover um elemento do conjunto
bool set_remover(SET *s, int elemento) {
    if (s == NULL)
        return false;
    return avl_remover(s->conjunto, elemento);
}

// Função para apagar o conjunto da memória
void set_apagar(SET **s) {
    if (*s != NULL) {
        avl_apagar(&(*s)->conjunto);  // Apagar a árvore AVL associada ao conjunto
        free(*s);
        *s = NULL;
    }
}

// Função para imprimir o conjunto
void set_imprimir(SET *s) {
    if (s != NULL)
        avl_imprimir(s->conjunto);
}

// Função para realizar a união de dois conjuntos
SET *set_uniao(SET *A, SET *B) {
    if (A == NULL)
        return B;
    if (B == NULL)
        return A;

    SET *uniao = set_criar();
    set_set_conjunto(uniao, avl_uniao(A->conjunto, B->conjunto));

    return uniao;
}

// Função para realizar a interseção de dois conjuntos
SET *set_interseccao(SET *A, SET *B) {
    if (A == NULL || B == NULL)
        return NULL;

    SET *intersecao = set_criar();
    set_set_conjunto(intersecao, avl_interseccao(A->conjunto, B->conjunto));

    return intersecao;
}
