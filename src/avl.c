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

// função de criar uma avl
AVL *avl_criar(void)
{
    AVL *arvore = (AVL *)malloc(sizeof(AVL)); // aloca espaço e verifica se foi bem alocado
    if (arvore != NULL)
    {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}
// função de apagar avl auxiliar
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
// função de apagar avl principal
void avl_apagar(AVL **arvore)
{
    avl_apagar_aux((*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

// função auxiliar que verifica a altura da arvore para saber se esta balanceada
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
// função que cria os nó usados na arvore
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

// Função para apagar um nó
bool avl_apaga_no(NO **no)
{
    if (*no == NULL)
        return false;
        
    item_apagar(&(*no)->item);
    free(*no);
    return true;
}

// função de rotação dir
NO *rodar_direita(NO *a)
{
    NO *b = a->fesq;   // cria um aux que recebe o esquerdo do no problema
    a->fesq = b->fdir; // esse esq recebe o direito que no caso é o direito do no problema
    b->fdir = a;       // para completa a rotação o direito recebe de fato a raiz a

    a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1; // atualiza a altura do no problema
    b->altura = max(avl_altura_no(b->fesq), a->altura) + 1;              // atualiza a altura do novo no b
    return b;
}
// função de rotação esq segue os mesmos parametros do da direita porem tudo a esquerda
NO *rodar_esquerda(NO *a)
{
    NO *b = a->fdir;
    a->fdir = b->fesq;
    b->fesq = a;
    a->altura = max(avl_altura_no(a->fesq), avl_altura_no(a->fdir)) + 1;
    b->altura = max(avl_altura_no(b->fdir), a->altura) + 1;
    return b;
}
// função de rotação esq/dir chama as funções na ordem necessária
NO *rodar_esquerda_direita(NO *a)
{
    a->fesq = rodar_esquerda(a->fesq);
    return rodar_direita(a);
}
// função de rotação dir/esq chama as funções na ordem necessária
NO *rodar_direita_esquerda(NO *a)
{
    a->fdir = rodar_direita(a->fdir);
    return rodar_esquerda(a);
}
// função aux para inserir um no em uma arvore
NO *avl_inserir_no(NO *raiz, NO *no)
{
    if (raiz == NULL) // caso de parada da recursao
        raiz = no;
    else if (item_get_chave(no->item) < item_get_chave(raiz->item)) // como é uma arvore binaria deve comparar as chaves
        raiz->fesq = avl_inserir_no(raiz->fesq, no);
    else if (item_get_chave(no->item) > item_get_chave(raiz->item))
        raiz->fdir = avl_inserir_no(raiz->fdir, no);

    raiz->altura = max(avl_altura_no(raiz->fesq), avl_altura_no(raiz->fdir)) + 1; // atualiza a altura apos a inserção

    // rebalanceamento da arvore atravez das rotações
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

    return raiz;
}
// função principal de inserção
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

// função de busca aux
NO *avl_buscar_aux(NO *n, int chave)
{
    if (n == NULL)
        return NULL;

    int chave_item = item_get_chave(n->item);

    if (chave_item == chave)
        return n;

    if (chave < chave_item) // compara as chaves
        return avl_buscar_aux(n->fesq, chave);
    else
        return avl_buscar_aux(n->fdir, chave);
}
/*Função busca o item dentro da arvore*/
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

// função aux para ajudar na remoção, poderia ser troca min direito
//  Função para trocar um nó pelo nó com o valor máximo à esquerda
void avl_troca_max_esq(NO *troca, NO *raiz, NO *ant)
{
    // Verifica se o nó troca tem um filho à direita
    if ((troca)->fdir != NULL)
    {
        // Chama recursivamente a função para encontrar o valor máximo à esquerda
        avl_troca_max_esq((troca)->fdir, raiz, troca);
        return;
    }

    // Caso inicial da troca
    if ((raiz) == (ant))
    {
        // Atualiza o ponteiro do pai para apontar para o filho à esquerda do nó troca
        (ant)->fesq = (troca)->fesq;
    }
    else
    {
        // Atualiza o ponteiro do pai para apontar para o filho à esquerda do nó troca
        (ant)->fdir = (troca)->fesq;
    }

    // Substitui o valor do nó raiz pelo valor do nó troca
    ITEM *temp = (raiz)->item;
    (raiz)->item = (troca)->item;

    // Libera a memória alocada para o nó troca
    item_apagar(&temp);
    free(troca);

    // Define o ponteiro do nó troca como NULL para evitar acesso acidental
    troca = NULL;
}

NO *avl_remover_aux(NO **raiz, int chave)
{
    // Se a raiz for nula, não há nada a ser removido
    if (*raiz == NULL)
        return NULL;

    // Verifica se a chave a ser removida é igual à chave do nó atual
    if (chave == item_get_chave((*raiz)->item))
    {
        // CASO 1 e 2: Nó possui um ou nenhum filho
        if ((*raiz)->fdir == NULL || (*raiz)->fesq == NULL)
        {
            NO *p = *raiz;
            if ((*raiz)->fdir != NULL)
            {
                // Se o nó tem um filho à direita, substitui o nó pelo filho à direita
                (*raiz) = (*raiz)->fdir;
            }
            else
            {
                // Se o nó tem um filho à esquerda ou nenhum filho, substitui o nó pelo filho à esquerda (que pode ser NULL)
                (*raiz) = (*raiz)->fesq;
            }

            // Desalocar o nó não utilizado
            avl_apaga_no(&p);
        }
        // CASO 3: Nó tem dois filhos
        else
        {
            // Troca o nó atual pelo nó que contém o valor máximo à esquerda
            avl_troca_max_esq((*raiz)->fesq, (*raiz), (*raiz));
        }
    }
    else if (chave < item_get_chave((*raiz)->item))
    {
        // Se a chave a ser removida é menor, busca e remove na subárvore esquerda
        (*raiz)->fesq = avl_remover_aux(&(*raiz)->fesq, chave);
    }
    else if (chave > item_get_chave((*raiz)->item))
    {
        // Se a chave a ser removida é maior, busca e remove na subárvore direita
        (*raiz)->fdir = avl_remover_aux(&(*raiz)->fdir, chave);
    }

    // Após a remoção, é necessário balancear a árvore
    if (*raiz != NULL)
    {
        // Atualiza a altura do nó atual
        (*raiz)->altura = max(avl_altura_no((*raiz)->fesq), avl_altura_no((*raiz)->fdir)) + 1;

        // Verifica e realiza rotações para manter o balanceamento
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

    // Retorna a raiz atualizada
    return *raiz;
}

bool avl_remover(AVL *T, int chave)
{
    // Verifica se a árvore e a raiz são válidas
    if (T == NULL)
        return false;
    if (T->raiz == NULL)
        return false;

    // Chama a função auxiliar para realizar a remoção
    avl_remover_aux(&T->raiz, chave);

    // Retorna verdadeiro indicando que a remoção foi bem-sucedida
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
void avl_imprimir(AVL *T)
{
    if (T == NULL)
        return;
    avl_imprimir_subarvore(T->raiz);
}

// Função auxiliar para unir duas árvores AVL
void avl_uniao_aux(AVL *C, NO *raiz)
{
    if (raiz == NULL) // verfica se a raiz é nula
        return;
    avl_inserir(C, item_get_chave(raiz->item)); // insere na arvore as raizes
    avl_uniao_aux(C, raiz->fesq);               // volta com recursão pela esquerda
    avl_uniao_aux(C, raiz->fdir);               // volta com recursão pela direita
}

AVL *avl_uniao(AVL *A, AVL *B)
{
    AVL *C = (AVL *)malloc(sizeof(AVL)); // cria uma nova arvore que resultara da uniao de A e B
    C = avl_criar();
    avl_uniao_aux(C, A->raiz); // primeiro insere todos os elementos da arvore A
    avl_uniao_aux(C, B->raiz); // apos isso insere todos os elementos da arvore B
    return C;
}

void avl_interseccao_aux(AVL *T3, NO *raiz1, AVL *T2)
{
    if (raiz1 == NULL) // verifica se a raiz é nula
        return;

    if (avl_buscar(T2, item_get_chave(raiz1->item)) != NULL) // busca na arvore 2 elementos em comum com a arvore 1 que esta sendo pecorrida atraves da sua raiz
        avl_inserir(T3, item_get_chave(raiz1->item));        // quando encontra esse elemento ela insere ele na nova arvore de intersecção

    avl_interseccao_aux(T3, raiz1->fesq, T2); // navega pela arvore 1
    avl_interseccao_aux(T3, raiz1->fdir, T2);
}

AVL *avl_interseccao(AVL *T1, AVL *T2)
{
    AVL *T3 = (AVL *)malloc(sizeof(AVL)); // cria uma nova arvore que resultara da intersecção de 1 e 2
    T3 = avl_criar();
    avl_interseccao_aux(T3, T1->raiz, T2);
    return T3;
}