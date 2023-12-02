#include "avl.h"

typedef struct node_ NODE;

struct node_ {
    int chave;
    struct avl_Node* esquerda;
    struct avl_Node* direita;
    int altura;
};


struct avl_ {
    NODE* raiz;
};

AVL* avl_criar();
void avl_destruir(AVL* tree);
void avl_inserir(AVL* tree, int chave);
void avl_remover(AVL* tree, int chave);
ITEM* avl_buscar(AVL* tree, int chave);
void avl_imprimir(AVL* tree);