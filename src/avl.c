#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    ITEM *item;
    struct No *fesq;
    struct No *fdir;
    int altura;
} NO;

struct avl
{
    NO *raiz;
    int profundidade;
};

AVL *avl_criar(void)
{
    AVL *arvore = (AVL *)malloc(sizeof(AVL));
    if (arvore != NULL)
    {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}

void avl_apagar_aux(NO *raiz)
{
    if (raiz != NULL)
    {
        avl_apagar_aux(raiz->fesq);
        avl_apagar_aux(raiz->fdir);
        item_apagar(&raiz->item);
        free(raiz);
    }
}

void avl_apagar(AVL **arvore)
{
    avl_apagar_aux((*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

int avl_altura_no(NO *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        return raiz->altura;
    }
}

NO *avl_cria_no(ITEM *item)
{
    NO *no = (NO *)malloc(sizeof(NO));
    if (no != NULL)
    {
        no->altura = 0;
        no->fdir = NULL;
        no->fesq = NULL;
        no->item = item;
    }
    return no;
}

bool avl_apaga_no(NO* no)
{
    item_apagar(no->item);
    free(no);
}

NO *rodar_direita(NO *a)
{
    NO *b = a->fesq;
    a->fesq = b->fdir;
    b->fdir = a;

    a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1;
    // b->altura = max(avl_altura_no(b->fesq), a->altura )+ 1;
    return b;
}

NO *rodar_esquerda(NO *a)
{
    NO *b = a->fdir;
    a->fdir = b->fesq;
    b->fesq = a;
    a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1;
    // b->altura = max(avl_altura_no(b->fdir), a->altura) + 1;
    return b;
}

NO *rodar_esquerda_direita(NO *a)
{
    a->fesq = rodar_esquerda(a->fesq);
    return rodar_direita(a);
}

NO *rodar_direita_esquerda(NO *a)
{
    a->fdir = rodar_direita(a->fdir);
    return rodar_esquerda(a);
}

NO *avl_inserir_no(NO *raiz, NO *no)
{
    if (raiz == NULL)
        raiz = no;
    else if (item_get_chave(no->item) < item_get_chave(raiz->item))
        raiz->fesq = avl_inserir_no(raiz->fesq, no);
    else if (item_get_chave(no->item) > item_get_chave(raiz->item))
        raiz->fdir = avl_inserir_no(raiz->fdir, no);

    raiz->altura = max(avl_altura_no(raiz->fesq), avl_altura_no(raiz->fdir)) + 1;

    if (avl_altura_no(raiz->fesq) - avl_altura_no(raiz->fdir) == -2)
    {
        if (item_get_chave(no->item) > item_get_chave(raiz->fdir->item))
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    }
    if (avl_altura_no(raiz->fesq) - avl_altura_no(raiz->fdir) == 2)
    {
        if (item_get_chave(no->item) < item_get_chave(raiz->fesq->item))
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }

    // printf("oi\n");
    return raiz;
}

bool avl_inserir(AVL *T, int chave)
{
    NO *novo;
    ITEM *item = item_criar(chave);

    if (T == NULL || item == NULL)
        return (false);

    novo = avl_cria_no(item);

    if (novo != NULL)
    {
        T->raiz = avl_inserir_no(T->raiz, novo);
        if (T->raiz != NULL)
            return (true);
        else 
            return false;
    }

    return (false);
}

NO *avl_buscar_aux(NO *n, int chave)
{
    if (n == NULL)
        return NULL;

    int chave_item = item_get_chave(n->item);

    if (chave_item == chave)
        return n;

    if (chave < chave_item)
        return avl_buscar_aux(n->fesq, chave);
    else
        return avl_buscar_aux(n->fdir, chave);
}

ITEM *avl_buscar(AVL *T, int chave)
{
    if (T != NULL)
    {
        NO *res = avl_buscar_aux(T->raiz, chave);
        if (res != NULL)
            return res->item;
    }
    return NULL;
}

void avl_troca_max_esq(NO *troca, NO *raiz, NO *ant)
{
    if ((troca)->fdir != NULL)
    {
        avl_troca_max_esq((troca)->fdir, raiz, troca);
        return;
    }

    // Caso onde na primeira iteração da troca já
    // não tem filho direto
    if ((raiz) == (ant))
    {
        (ant)->fesq = (troca)->fesq;
    }
    else
    {
        (ant)->fdir = (troca)->fesq;
    }

    (raiz)->item = (troca)->item;
    free(troca);
    troca = NULL;
}

NO *avl_remover_aux(NO **raiz, int chave)
{

    if (*raiz == NULL)
        return NULL;

    if (chave == item_get_chave((*raiz)->item))
    {
        
        // CASO 1 e 2: Nó possui um ou nenhum filho
        if ((*raiz)->fdir == NULL || (*raiz)->fesq == NULL)
        {
            NO *p = (*raiz);
            if ((*raiz)->fdir != NULL)
            {
                (*raiz) = (*raiz)->fdir;
            }
            else
            {
                (*raiz) = (*raiz)->fesq;
            }

            avl_apaga_no(p);
        }
        // CASO 3: Nó tem dois filhos
        else
        {
            avl_troca_max_esq((*raiz)->fesq, (*raiz), (*raiz));
        }
    }
    else if (chave < item_get_chave((*raiz)->item))
    {
        (*raiz)->fesq = avl_remover_aux(&(*raiz)->fesq, chave);
    }
    else if (chave > item_get_chave((*raiz)->item))
    {
        (*raiz)->fdir = avl_remover_aux(&(*raiz)->fdir, chave);
    }

    if (*raiz != NULL)
    {
        // Código pra balancear a árvore (Só copiei do slide 0 chance de funcionar)
        (*raiz)->altura = max(avl_altura_no((*raiz)->fesq), avl_altura_no((*raiz)->fdir)) + 1;

        if (avl_altura_no((*raiz)->fesq) - avl_altura_no((*raiz)->fdir) == -2)
        {
            if (avl_altura_no((*raiz)->fdir->fesq) <= avl_altura_no((*raiz)->fdir->fdir))
                (*raiz) = rodar_esquerda((*raiz));
            else
                (*raiz) = rodar_direita_esquerda((*raiz));
        }

        if (avl_altura_no((*raiz)->fesq) - avl_altura_no((*raiz)->fdir) == 2)
        {
            if (avl_altura_no((*raiz)->fesq->fesq) >= avl_altura_no((*raiz)->fesq->fdir))
                (*raiz) = rodar_direita((*raiz));
            else
                (*raiz) = rodar_esquerda_direita((*raiz));
        }
    }

    return *raiz;
}

bool avl_remover(AVL *T, int chave)
{
    if (T == NULL)
        return false;
    if (T->raiz == NULL)
        return false;

    avl_remover_aux(&T->raiz, chave);

    return true;
}

// Função auxiliar para imprimir uma subárvore AVL
void avl_imprimir_subarvore(NO *raiz)
{
    if (raiz != NULL)
    {
        avl_imprimir_subarvore(raiz->fesq);
        printf("%d ", item_get_chave(raiz->item));
        avl_imprimir_subarvore(raiz->fdir);
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

    printf("Altura da AVL: %d\n", avl_altura_no(tree->raiz));
}
