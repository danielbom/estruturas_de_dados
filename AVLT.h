/*
 * AVL -> Adelson-Velskii & Landis - 1962
*/
#include "tipos_primarios.h"
#include "NoTree.h"
#include <stdio.h>
#include <stdlib.h>

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
NoTree *search_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *)); // OK

/* FUNCOES DE INSERCAO */
void add_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *));
static NoTree *_add_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *));

/* FUNCOES DE REMOCAO */
void remove_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *));
static NoTree *_remove_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *));

void clear_AVLT(AVLT *L); // OK

/* FUNCOES AUXILIARES */
bool empyt_AVLT(AVLT *A);                                  // OK
void in_order_AVLT(AVLT *A, void (*print)(const void *));  // OK
void pre_order_AVLT(AVLT *A, void (*print)(const void *)); // OK
void pos_order_AVLT(AVLT *A, void (*print)(const void *)); // OK

static void print_decorator_AVLT(const void *dado, void (*print)(const void *)); // OK

int heigth_AVLT(AVLT *A);            // OK
static int _heigth_AVLT(NoTree *no); // OK

static NoTree *_check_unbalanced(NoTree *no, void *elem, int (*cmp)(const void *, const void *)); // OK

static NoTree *rotate_RR_AVLT(NoTree *no); // OK
static NoTree *rotate_LL_AVLT(NoTree *no); // OK
static NoTree *rotate_RL_AVLT(NoTree *no); // OK
static NoTree *rotate_LR_AVLT(NoTree *no); // OK

void *min_AVLT(AVLT *B);              // OK
void *max_AVLT(AVLT *B);              // OK
static NoTree *_min_AVLT(NoTree *no); // OK
static NoTree *_max_AVLT(NoTree *no); // OK

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
void add_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *))
{
    A->raiz = _add_AVLT(A, A->raiz, elem, cmp);
}
static NoTree *_add_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *))
{
    if (no == NULL)
    {
        A->qtde++;
        no = new_NoTree(elem, A->size, 0);
    }
    else if (LESS_THAN(cmp(elem, no->dado)))
    {
        no->esq = _add_AVLT(A, no->esq, elem, cmp);
        no = _check_unbalanced(no, elem, cmp);
    }
    else if (GREATER_THAN(cmp(elem, no->dado)))
    {
        no->dir = _add_AVLT(A, no->dir, elem, cmp);
        no = _check_unbalanced(no, elem, cmp);
    }
    return no;
}
/* FUNCOES DE REMOCAO */
void remove_AVLT(AVLT *A, void *elem, int (*cmp)(const void *, const void *))
{
    A->raiz = _remove_AVLT(A, A->raiz, elem, cmp);
}
static NoTree *_remove_AVLT(AVLT *A, NoTree *no, void *elem, int (*cmp)(const void *, const void *))
{
    if (no == NULL)
    {
        return NULL;
    }
    // Movimentando
    if (LESS_THAN(cmp(elem, no->dado)))
    {
        no->esq = _remove_AVLT(A, no->esq, elem, cmp);
        no = _check_unbalanced(no, elem, cmp);
        return no;
    }
    if (GREATER_THAN(cmp(elem, no->dado)))
    {
        no->dir = _remove_AVLT(A, no->dir, elem, cmp);
        no = _check_unbalanced(no, elem, cmp);
        return no;
    }
    // Removendo
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
    no->dir = _remove_AVLT(A, no->dir, no->dado, cmp);
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

void *min_AVLT(AVLT *B)
{
    NoTree *aux = _min_AVLT(B->raiz);
    return aux == NULL ? NULL : aux->dado;
}
void *max_AVLT(AVLT *B)
{
    NoTree *aux = _max_AVLT(B->raiz);
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