#include "set.h"
#include "avl.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funções para alternar entre o teste da AVL e o teste do set
// NÂO DEIXE OS DOIS DEFINIDOS AO MSM TEMPO, O PROGRAMA NÂO VAI COMPILAR!!!!!
#define TEST_AVL
// #define TEST_SET

#ifdef TEST_AVL

void inserir(AVL *t, int n)
{
    if (!avl_inserir(t, n))
        printf("Falha ao inserir %d na AVL\n", n);
    else
        printf("%d inserido na AVL\n", n);
}

void buscar(AVL *t, int n)
{
    if (avl_buscar(t, n) == NULL)
        printf("%d não encontrado na AVL\n", n);
    else
        printf("%d presente na AVL\n", n);
}

void remover(AVL *t, int n)
{
    if (!avl_remover(t, n))
        printf("%d não presente na AVL\n", n);
    else
        printf("%d removido da AVL\n", n);
}

int main()
{
    // srand(time(NULL));

    // Criar uma árvore AVL
    AVL *minha_avl = avl_criar();

    // Inserir elementos na árvore
    inserir(minha_avl, 5);
    inserir(minha_avl, 3);
    inserir(minha_avl, 8);
    inserir(minha_avl, 2);
    inserir(minha_avl, 4);
    inserir(minha_avl, 7);
    inserir(minha_avl, 9);

    // Imprimir árvore AVL
    printf("Árvore AVL:\n");
    avl_imprimir(minha_avl);

    printf("================================\n");

    // Buscar um elemento na árvore AVL
    buscar(minha_avl, 6);
    buscar(minha_avl, 3);
    buscar(minha_avl, 8);
    buscar(minha_avl, 2);
    buscar(minha_avl, 4);
    buscar(minha_avl, 7);
    buscar(minha_avl, 9);

    printf("================================\n");

    // Remover um elemento da árvore AVL
    remover(minha_avl, 5);
    remover(minha_avl, 3);
    remover(minha_avl, 8);
    remover(minha_avl, 2);

    avl_imprimir(minha_avl);

    remover(minha_avl, 4);
    remover(minha_avl, 7);
    remover(minha_avl, 9);

    // Imprimir árvore AVL após a remoção
    // printf("\nÁrvore AVL após a remoção do elemento %d:\n", chave_para_remover);
    avl_imprimir(minha_avl);

    printf("================================\n");


    printf("Teste de força bruta, inserção de 1000 itens aleatórios\n");

    const int tam_teste = 100;
    int lista_teste[tam_teste];

    for (int i = 0; i < tam_teste; i++)
    {
        lista_teste[i] = rand();
        // printf("%d\n", lista_teste[i]);

        // Teste com inserções em ordem crescente
        // lista_teste[i] = i;

        // Teste com inserções em ordem decrescente
        // lista_teste[i] = tam_teste - i;
    }

    for (int i = 0; i < tam_teste; i++)
    {
        inserir(minha_avl, lista_teste[i]);
    }

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