#include "avl.h"
#include <stdio.h>

typedef struct node_ NODE;

struct node_
{
    ITEM *item;
    NODE *esquerda;
    NODE *direita;
    int altura;
};

struct avl_
{
    NODE *raiz;
};

// Função auxiliar para criar um novo nó AVL
NODE *avl_criar_no(int chave)
{
    NODE *novo_no = (NODE *)malloc(sizeof(NODE));
    if (novo_no != NULL)
    {
        item_set_chave(novo_no->item, chave);
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        novo_no->altura = 1; // Altura inicial de um nó é 1
    }
    return novo_no;
}

// Função pública para criar uma árvore AVL
AVL *avl_criar()
{
    AVL *nova_avl = (AVL *)malloc(sizeof(AVL));
    if (nova_avl != NULL)
    {
        nova_avl->raiz = NULL;
    }
    return nova_avl;
}

// Função auxiliar para destruir uma subárvore AVL
void avl_destruir_subarvore(NODE *raiz)
{
    if (raiz != NULL)
    {
        avl_destruir_subarvore(raiz->esquerda);
        avl_destruir_subarvore(raiz->direita);
        free(raiz);
    }
}

// Função pública para destruir a árvore AVL
void avl_destruir(AVL *tree)
{
    if (tree != NULL)
    {
        avl_destruir_subarvore(tree->raiz);
        free(tree);
    }
}

// Função auxiliar para obter a altura de um nó
int avl_altura(NODE *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return no->altura;
}

// Função auxiliar para calcular o fator de balanceamento de um nó
int avl_fator_balanceamento(NODE *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return avl_altura(no->esquerda) - avl_altura(no->direita);
}

// Função auxiliar para atualizar a altura de um nó
void avl_atualizar_altura(NODE *no)
{
    if (no != NULL)
    {
        int altura_esquerda = avl_altura(no->esquerda);
        int altura_direita = avl_altura(no->direita);
        no->altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
    }
}

// Função auxiliar para rotacionar à direita em torno do nó 'y'
NODE *avl_rotacao_direita(NODE *y)
{
    NODE *x = y->esquerda;
    NODE *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    avl_atualizar_altura(y);
    avl_atualizar_altura(x);

    return x;
}

// Função auxiliar para rotacionar à esquerda em torno do nó 'x'
NODE *avl_rotacao_esquerda(NODE *x)
{
    NODE *y = x->direita;
    NODE *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    avl_atualizar_altura(x);
    avl_atualizar_altura(y);

    return y;
}

// Função principal para inserir um elemento na árvore AVL
NODE *avl_inserir_no(NODE *no, int chave)
{
    // Etapa de inserção BST
    if (no == NULL)
    {
        return avl_criar_no(chave);
    }

    if (chave < item_get_chave(no->item))
    {
        no->esquerda = avl_inserir_no(no->esquerda, chave);
    }
    else if (chave > item_get_chave(no->item))
    {
        no->direita = avl_inserir_no(no->direita, chave);
    }
    else
    {
        // Chaves iguais não são permitidas
        return no;
    }

    // Atualizar altura do nó atual
    avl_atualizar_altura(no);

    // Calcular fator de balanceamento
    int balanceamento = avl_fator_balanceamento(no);

    // Casos de rotação

    // Rotação à direita (Left-Left)
    if (balanceamento > 1 && chave < item_get_chave(no->esquerda->item))
    {
        return avl_rotacao_direita(no);
    }

    // Rotação à esquerda (Right-Right)
    if (balanceamento < -1 && chave > item_get_chave(no->direita->item))
    {
        return avl_rotacao_esquerda(no);
    }

    // Rotação à esquerda-direita (Left-Right)
    if (balanceamento > 1 && chave > item_get_chave(no->esquerda->item))
    {
        no->esquerda = avl_rotacao_esquerda(no->esquerda);
        return avl_rotacao_direita(no);
    }

    // Rotação à direita-esquerda (Right-Left)
    if (balanceamento < -1 && chave < item_get_chave(no->direita->item))
    {
        no->direita = avl_rotacao_direita(no->direita);
        return avl_rotacao_esquerda(no);
    }

    return no;
}

// Função pública para inserir um elemento na árvore AVL
void avl_inserir(AVL *tree, int chave)
{
    if (tree != NULL)
    {
        tree->raiz = avl_inserir_no(tree->raiz, chave);
    }
}

// Função auxiliar para encontrar o nó mínimo em uma árvore AVL
NODE *avl_encontrar_minimo(NODE *no)
{
    while (no->esquerda != NULL)
    {
        no = no->esquerda;
    }
    return no;
}

// Função auxiliar para remover um nó em uma árvore AVL
NODE *avl_remover_no(NODE *raiz, int chave)
{
    // Etapa de remoção BST
    if (raiz == NULL)
    {
        return raiz;
    }

    if (chave < item_get_chave(raiz->item))
    {
        raiz->esquerda = avl_remover_no(raiz->esquerda, chave);
    }
    else if (chave > item_get_chave(raiz->item))
    {
        raiz->direita = avl_remover_no(raiz->direita, chave);
    }
    else
    {
        // Nó encontrado, realizar a remoção

        // Nó com um filho ou nenhum filho
        if (raiz->esquerda == NULL || raiz->direita == NULL)
        {
            NODE *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            // Nenhum filho
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {                  // Um filho
                *raiz = *temp; // Copiar o conteúdo do nó não-nulo
            }

            free(temp);
        }
        else
        {
            // Nó com dois filhos, obter o sucessor in-order (mínimo da subárvore direita)
            NODE *temp = avl_encontrar_minimo(raiz->direita);

            // Copiar o sucessor in-order para este nó
            item_set_chave(raiz->item, item_get_chave(temp->item));

            // Remover o sucessor in-order
            raiz->direita = avl_remover_no(raiz->direita, item_get_chave(temp->item));
        }
    }

    // Se a árvore tinha apenas um nó, então retornar
    if (raiz == NULL)
    {
        return raiz;
    }

    // Atualizar altura do nó atual
    avl_atualizar_altura(raiz);

    // Calcular fator de balanceamento
    int balanceamento = avl_fator_balanceamento(raiz);

    // Casos de rotação

    // Rotação à direita (Left-Left)
    if (balanceamento > 1 && avl_fator_balanceamento(raiz->esquerda) >= 0)
    {
        return avl_rotacao_direita(raiz);
    }

    // Rotação à esquerda (Right-Right)
    if (balanceamento < -1 && avl_fator_balanceamento(raiz->direita) <= 0)
    {
        return avl_rotacao_esquerda(raiz);
    }

    // Rotação à esquerda-direita (Left-Right)
    if (balanceamento > 1 && avl_fator_balanceamento(raiz->esquerda) < 0)
    {
        raiz->esquerda = avl_rotacao_esquerda(raiz->esquerda);
        return avl_rotacao_direita(raiz);
    }

    // Rotação à direita-esquerda (Right-Left)
    if (balanceamento < -1 && avl_fator_balanceamento(raiz->direita) > 0)
    {
        raiz->direita = avl_rotacao_direita(raiz->direita);
        return avl_rotacao_esquerda(raiz);
    }

    return raiz;
}

// Função pública para remover um elemento na árvore AVL
void avl_remover(AVL *tree, int chave)
{
    if (tree != NULL)
    {
        tree->raiz = avl_remover_no(tree->raiz, chave);
    }
}

// Função auxiliar para buscar um elemento em uma subárvore AVL
NODE *avl_buscar_no(NODE *raiz, int chave)
{
    if (raiz == NULL || item_get_chave(raiz->item) == chave)
    {
        return raiz;
    }

    if (chave < item_get_chave(raiz->item))
    {
        return avl_buscar_no(raiz->esquerda, chave);
    }

    return avl_buscar_no(raiz->direita, chave);
}

// Função pública para buscar um elemento na árvore AVL
ITEM *avl_buscar(AVL *tree, int chave)
{
    if (tree != NULL)
    {
        return avl_buscar_no(tree->raiz, chave)->item;
    }
    return NULL;
}

// Função auxiliar para imprimir uma subárvore AVL
void avl_imprimir_subarvore(NODE *raiz)
{
    if (raiz != NULL)
    {
        avl_imprimir_subarvore(raiz->esquerda);
        printf("%d ", item_get_chave(raiz->item));
        avl_imprimir_subarvore(raiz->direita);
    }
}

// Função pública para imprimir a árvore AVL
void avl_imprimir(AVL *tree)
{
    if (tree != NULL)
    {
        avl_imprimir_subarvore(tree->raiz);
        printf("\n");
    }
    else
    {
        printf("AVL vazia.\n");
    }
}