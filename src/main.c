#include "set.h"
#include "avl.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

// Funções para alternar entre o teste da AVL e o teste do set
// NÂO DEIXE OS DOIS DEFINIDOS AO MSM TEMPO, O PROGRAMA NÂO VAI COMPILAR!!!!!
#define TEST_AVL
// #define TEST_SET

#ifdef TEST_AVL

int main()
{
    // Criar uma árvore AVL
    AVL *minha_avl = avl_criar();

    // Inserir elementos na árvore
    avl_inserir(minha_avl, 5);
    avl_inserir(minha_avl, 3);
    avl_inserir(minha_avl, 8);
    avl_inserir(minha_avl, 2);
    avl_inserir(minha_avl, 4);
    avl_inserir(minha_avl, 7);
    avl_inserir(minha_avl, 9);

    // Imprimir árvore AVL
    printf("Árvore AVL:\n");
    avl_imprimir(minha_avl);

    // Buscar um elemento na árvore AVL
    int chave_para_buscar = 4;
    ITEM *resultado_busca = avl_buscar(minha_avl, chave_para_buscar);

    if (resultado_busca != NULL)
    {
        printf("Elemento %d encontrado na árvore AVL.\n", chave_para_buscar);
    }
    else
    {
        printf("Elemento %d não encontrado na árvore AVL.\n", chave_para_buscar);
    }

    // Remover um elemento da árvore AVL
    int chave_para_remover = 3;
    avl_remover(minha_avl, chave_para_remover);

    // Imprimir árvore AVL após a remoção
    printf("\nÁrvore AVL após a remoção do elemento %d:\n", chave_para_remover);
    avl_imprimir(minha_avl);

    // Destruir a árvore AVL
    avl_apagar(&minha_avl);

    return 0;
}

#endif

#ifdef TEST_SET

int main(int argc, char *argv[])
{
    SET *A, *B;
    int n_a, n_b, x;
    int op;

    A = set_criar();
    B = set_criar();

    scanf("%d %d", &n_a, &n_b);

    for (int i = 0; i < n_a; i++)
    {
        scanf("%d", &x);
        set_inserir(A, x);
    }

    for (int i = 0; i < n_b; i++)
    {
        scanf("%d", &x);
        set_inserir(B, x);
    }

    scanf("%d", &op);

    switch (op)
    {
    case 1:
    {
        int num;
        scanf("%d", &num);
        if (set_pertence(A, num))
            printf("Pertence.");
        else
            printf("Não Pertence.");
        break;
    }
    case 2:
    {
        SET *C = set_uniao(A, B);
        set_imprimir(C);
        set_apagar(&C);
        break;
    }
    case 3:
    {
        SET *C = set_interseccao(A, B);
        set_imprimir(C);
        set_apagar(&C);
        break;
    }
    case 4:
    {
        int num;
        scanf("%d", &num);
        set_remover(A, num);
        set_imprimir(A);
    }
    }

    set_apagar(&A);
    set_apagar(&B);

    return 0;
}
#endif