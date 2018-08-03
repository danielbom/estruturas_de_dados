// AVL -> Adelson-Velskii & Landis - 1962

#include "../tipos_primarios.h"
#include "NoTree.h"

typedef struct AVLT
{
    NoTree *raiz;
    int qtde;
    size_t size;
} AVLT;

/* CONSTRUTOR E DESTRUTOR */
AVLT *new_AVLT(size_t size);
void delete_AVLT(AVLT **A);

/* FUNCOES DE BUSCA */
NoTree *search_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *)); // OK 30/07/2018

/* FUNCOES DE INSERCAO */
bool add_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *));                                   // OK 30/07/2018
static NoTree *_add_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *add); // OK 30/07/2018

/* FUNCOES DE REMOCAO */
bool remove_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *));                                       // OK 30/07/2018
static NoTree *_remove_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *removed); // OK 30/07/2018

void clear_AVLT(AVLT *L); // OK 30/07/2018

/* FUNCOES AUXILIARES */
bool empyt_AVLT(AVLT *A);                                  // OK 30/07/2018
void in_order_AVLT(AVLT *A, void (*print)(const void *));  // OK 30/07/2018
void pre_order_AVLT(AVLT *A, void (*print)(const void *)); // OK 30/07/2018
void pos_order_AVLT(AVLT *A, void (*print)(const void *)); // OK 30/07/2018

static void print_decorator_AVLT(const void *dado, void (*print)(const void *)); // OK 30/07/2018

int heigth_AVLT(AVLT *A);            // OK 30/07/2018
static int _heigth_AVLT(NoTree *no); // OK 30/07/2018

static NoTree *_check_unbalanced(NoTree *no, void *elem, int (*cmp)(const void *, const void *)); // OK 30/07/2018

static NoTree *rotate_RR_AVLT(NoTree *no); // OK 30/07/2018
static NoTree *rotate_LL_AVLT(NoTree *no); // OK 30/07/2018
static NoTree *rotate_RL_AVLT(NoTree *no); // OK 30/07/2018
static NoTree *rotate_LR_AVLT(NoTree *no); // OK 30/07/2018

void *min_AVLT(AVLT *A);              // OK 30/07/2018
void *max_AVLT(AVLT *A);              // OK 30/07/2018
static NoTree *_min_AVLT(NoTree *no); // OK 30/07/2018
static NoTree *_max_AVLT(NoTree *no); // OK 30/07/2018

/* IMPLEMENTACOES AVLT */

/* CONSTRUTOR E DESTRUTOR */
AVLT *new_AVLT(size_t size)
{
    AVLT *A = (AVLT *)malloc(sizeof(AVLT));
    A->raiz = NULL;
    A->qtde = 0;
    A->size = size;
}
void delete_AVLT(AVLT **A)
{
    clear_AVLT(*A);
    free(*A);
    *A = NULL;
}

/* FUNCOES DE BUSCA */
NoTree *search_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *))
{
    NoTree *_search_AVLT(NoTree * no, void *elem, int (*cmp)(const void *, const void *))
    {
        if (no == NULL)
            return NULL;
        if (cmp(elem, no->dado) > 0)
            return _search_AVLT(no->dir, elem, cmp);
        if (cmp(elem, no->dado) < 0)
            return _search_AVLT(no->esq, elem, cmp);
        return no;
    }
    return _search_AVLT(A->raiz, elem, cmp);
}

/* FUNCOES DE INSERCAO */
bool add_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *))
{
    bool _add = false;
    A->raiz = _add_AVLT(A, A->raiz, elem, cmp, &_add);
    return _add;
}
static NoTree *_add_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *add)
{
    if (no == NULL)
    {
        no = new_NoTree(elem, A->size);
        if (no != NULL)
        {
            *add = true;
            A->qtde++;
        }
    }
    else if (LESS_THAN(cmp(elem, no->dado)))
    {
        no->esq = _add_AVLT(A, no->esq, elem, cmp, add);
        no = *add ? _check_unbalanced(no, elem, cmp) : no;
    }
    else if (GREATER_THAN(cmp(elem, no->dado)))
    {
        no->dir = _add_AVLT(A, no->dir, elem, cmp, add);
        no = *add ? _check_unbalanced(no, elem, cmp) : no;
    }
    return no;
}
/* FUNCOES DE REMOCAO */
bool remove_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *))
{
    bool _removed = false;
    A->raiz = _remove_AVLT(A, A->raiz, elem, cmp, &_removed);
    return _removed;
}
static NoTree *_remove_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *removed)
{
    if (no == NULL)
    {
        return NULL;
    }
    // Movimentando
    if (LESS_THAN(cmp(elem, no->dado)))
    {
        no->esq = _remove_AVLT(A, no->esq, elem, cmp, removed);
        no = *removed ? _check_unbalanced(no, elem, cmp) : no;
        return no;
    }
    if (GREATER_THAN(cmp(elem, no->dado)))
    {
        no->dir = _remove_AVLT(A, no->dir, elem, cmp, removed);
        no = *removed ? _check_unbalanced(no, elem, cmp) : no;
        return no;
    }
    // Removendo
    *removed = true;
    if (no->dir == NULL && no->esq == NULL)
    {
        delete_NoTree(&no);
        A->qtde--;
        return NULL;
    }
    if (no->dir == NULL && no->esq != NULL)
    {
        NoTree *esq = no->esq;
        delete_NoTree(&no);
        A->qtde--;
        return esq;
    }
    if (no->dir != NULL && no->esq == NULL)
    {
        NoTree *dir = no->dir;
        delete_NoTree(&no);
        A->qtde--;
        return dir;
    }

    NoTree *aux = _min_AVLT(no->dir);

    copy_NoTree(no, aux);
    no->dir = _remove_AVLT(A, no->dir, no->dado, cmp, removed);
    return no;
}
void clear_AVLT(AVLT *L)
{
    NoTree *_clear_AVLT(NoTree * *no)
    {
        if (*no != NULL)
        {
            (*no)->esq = _clear_AVLT(&((*no)->esq));
            (*no)->dir = _clear_AVLT(&((*no)->dir));
            delete_NoTree(no);
        }
        return NULL;
    }
    L->raiz = _clear_AVLT(&(L->raiz));
    L->qtde = 0;
}

/* FUNCOES AUXILIARES */
bool empyt_AVLT(AVLT *A)
{
    return A->qtde == 0;
}
void in_order_AVLT(AVLT *A, void (*print)(const void *))
{
    void _in_order_AVLT(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            _in_order_AVLT(no->esq, print);
            print_decorator_AVLT(no->dado, print);
            _in_order_AVLT(no->dir, print);
        }
    }
    printf("( ");
    _in_order_AVLT(A->raiz, print);
    printf(")");
}
void pre_order_AVLT(AVLT *A, void (*print)(const void *))
{
    void _pre_order_AVLT(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            print_decorator_AVLT(no->dado, print);
            _pre_order_AVLT(no->esq, print);
            _pre_order_AVLT(no->dir, print);
        }
    }
    printf("( ");
    _pre_order_AVLT(A->raiz, print);
    printf(")");
}
void pos_order_AVLT(AVLT *A, void (*print)(const void *))
{
    void _pos_order_AVLT(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            _pos_order_AVLT(no->esq, print);
            _pos_order_AVLT(no->dir, print);
            print_decorator_AVLT(no->dado, print);
        }
    }
    printf("( ");
    _pos_order_AVLT(A->raiz, print);
    printf(")");
}

static void print_decorator_AVLT(const void *dado, void (*print)(const void *))
{
    print(dado);
    printf(" ");
}

int heigth_AVLT(AVLT *A)
{
    return _heigth_AVLT(A->raiz);
}
static int _heigth_AVLT(NoTree *no)
{
    if (no == NULL)
        return -1;
    int esq = _heigth_AVLT(no->esq);
    int dir = _heigth_AVLT(no->dir);
    return (dir > esq ? dir : esq) + 1;
}

static NoTree *_check_unbalanced(NoTree *no, void *elem, int (*cmp)(const void *, const void *))
{
    int esq = _heigth_AVLT(no->esq);
    int dir = _heigth_AVLT(no->dir);
    int unbalanced_factor = dir - esq;
    if (unbalanced_factor < -1)
        no = LESS_THAN(cmp(elem, no->esq->dado)) ? rotate_RR_AVLT(no) : rotate_RL_AVLT(no);
    else if (unbalanced_factor > 1)
        no = GREATER_THAN(cmp(elem, no->dir->dado)) ? rotate_LL_AVLT(no) : rotate_LR_AVLT(no);
    return no;
}

static NoTree *rotate_RR_AVLT(NoTree *no)
{
    NoTree *esq = no->esq;
    no->esq = esq->dir;
    esq->dir = no;
    return esq;
}
static NoTree *rotate_LL_AVLT(NoTree *no)
{
    NoTree *dir = no->dir;
    no->dir = dir->esq;
    dir->esq = no;
    return dir;
}
static NoTree *rotate_RL_AVLT(NoTree *no)
{
    no->esq = rotate_LL_AVLT(no->esq);
    return rotate_RR_AVLT(no);
}
static NoTree *rotate_LR_AVLT(NoTree *no)
{
    no->dir = rotate_RR_AVLT(no->dir);
    return rotate_LL_AVLT(no);
}

void *min_AVLT(AVLT *A)
{
    NoTree *aux = _min_AVLT(A->raiz);
    return aux == NULL ? NULL : aux->dado;
}
void *max_AVLT(AVLT *A)
{
    NoTree *aux = _max_AVLT(A->raiz);
    return aux == NULL ? NULL : aux->dado;
}

static NoTree *_min_AVLT(NoTree *no)
{
    if (no == NULL)
        return NULL;
    NoTree *aux = no;
    while (aux->esq != NULL)
        aux = aux->esq;
    return aux;
}
static NoTree *_max_AVLT(NoTree *no)
{
    if (no == NULL)
        return NULL;
    NoTree *aux = no;
    while (aux->dir != NULL)
        aux = aux->dir;
    return aux;
}