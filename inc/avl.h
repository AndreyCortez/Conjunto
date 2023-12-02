#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "item.h"

// Estrutura do TAD AVL
typedef struct avl_ AVL;

// Funções públicas do TAD AVL
AVL* avl_criar();
void avl_destruir(AVL* tree);
void avl_inserir(AVL* tree, int chave);
void avl_remover(AVL* tree, int chave);
ITEM* avl_buscar(AVL* tree, int chave);
void avl_imprimir(AVL* tree);

#endif // AVL_TREE_H
