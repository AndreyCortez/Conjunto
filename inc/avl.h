#ifndef AVL_H
	#define AVL_H
	
	#include <stdbool.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "item.h"
    #define max(a, b) ((a > b) ? a : b)
	typedef struct avl AVL;

	AVL* avl_criar();
	void avl_apagar(AVL **arvore);
	bool avl_inserir(AVL* T, int chave);
	bool avl_remover(AVL *T, int chave);
	ITEM* avl_buscar(AVL* T, int chave);
	void avl_imprimir(AVL* T);
	AVL *avl_uniao(AVL *A, AVL *B);
	AVL* avl_interseccao(AVL *T1, AVL *T2);

#endif