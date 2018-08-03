// RBT -> Red-Black Tree

#include "../tipos_primarios.h"
#include "NoTree.h"

typedef struct
{
    NoTree *raiz;
    int qtde;
    size_t size;
} RBT;

/* CONSTRUTOR E DESTRUTOR */
RBT *new_RBT(size_t size);
void delete_RBT(RBT **RB);

/* FUNCOES DE BUSCA */
NoTree *search_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *)); // OK 30/07/2018

/* FUNCOES DE INSERCAO */
bool add_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *));                                   // TODO
static NoTree *_add_RBT(RBT *RB, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *add); // TODO

/* FUNCOES DE REMOCAO */
bool remove_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *));                                       // TODO
static NoTree *_remove_RBT(RBT *RB, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *removed); // TODO

void clear_RBT(RBT *RB); // OK 30/07/2018

/* FUNCOES AUXILIARES */
bool empyt_RBT(RBT *RB);                                  // OK 30/07/2018
void in_order_RBT(RBT *RB, void (*print)(const void *));  // OK 30/07/2018
void pre_order_RBT(RBT *RB, void (*print)(const void *)); // OK 30/07/2018
void pos_order_RBT(RBT *RB, void (*print)(const void *)); // OK 30/07/2018

static void print_decorator_RBT(const void *dado, void (*print)(const void *)); // OK 30/07/2018

int heigth_RBT(RBT *RB);            // OK 30/07/2018
static int _heigth_RBT(NoTree *no); // OK 30/07/2018

static NoTree *_check_unbalanced(NoTree *no, void *elem, int (*cmp)(const void *, const void *)); // TODO

static NoTree *rotate_RR_RBT(NoTree *no); // OK 30/07/2018
static NoTree *rotate_LL_RBT(NoTree *no); // OK 30/07/2018
static NoTree *rotate_RL_RBT(NoTree *no); // OK 30/07/2018
static NoTree *rotate_LR_RBT(NoTree *no); // OK 30/07/2018

void *min_RBT(RBT *RB);
void *max_RBT(RBT *RB);
static NoTree *_min_RBT(NoTree *no);
static NoTree *_max_RBT(NoTree *no);

/* IMPLEMENTACOES RBT */

/* CONSTRUTOR E DESTRUTOR */
RBT *new_RBT(size_t size)
{
    RBT *RB = malloc(sizeof(RBT));
    RB->raiz = NULL;
    RB->qtde = 0;
    RB->size = size;
}
void delete_RBT(RBT **RB)
{
    clear_RBT(*RB);
    free(*RB);
    *RB = NULL;
}
/* FUNCOES DE BUSCA */
NoTree *search_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *))
{
    NoTree *_search_RBT(NoTree * no, void *elem, int (*cmp)(const void *, const void *))
    {
        if (no == NULL)
            return NULL;
        if (GREATER_THAN(cmp(elem, no->dado)))
            return _search_RBT(no->dir, elem, cmp);
        if (LESS_THAN(cmp(elem, no->dado)))
            return _search_RBT(no->esq, elem, cmp);
        return no;
    }
    return _search_RBT(RB->raiz, elem, cmp);
}

/* FUNCOES DE INSERCAO */
bool add_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *))
{
    if (RB->raiz == NULL)
    {
        RB->raiz = new_NoTree(elem, RB->size);
        RB->raiz->cor = BLACK;
        RB->qtde++;
        return true;
    }
    bool _add = false;
    RB->raiz = _add_RBT(RB, RB->raiz, elem, cmp, &_add);
    RB->qtde += _add;
    return _add;
}
static NoTree *_add_RBT(RBT *RB, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *add)
{
    if (no == NULL)
    {
        no = new_NoTree(elem, RB->size);
        *add = no != NULL;
    }
    else if (LESS_THAN(cmp(elem, no->dado)))
        no->esq = _add_RBT(RB, no->esq, elem, cmp, add);
    else if (GREATER_THAN(cmp(elem, no->dado)))
        no->dir = _add_RBT(RB, no->dir, elem, cmp, add);
    no = *add ? _check_unbalanced(no, elem, cmp) : no;
    return no;
}
/* FUNCOES DE REMOCAO */
bool remove_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *))
{
    if (RB->raiz == NULL)
        return false;

    bool _removed = false;
    RB->raiz = _remove_RBT(RB, RB->raiz, elem, cmp, &_removed);
    RB->qtde -= _removed;
    return _removed;
}
static NoTree *_remove_RBT(RBT *RB, NoTree *no, void *elem, int (*cmp)(const void *, const void *), bool *removed)
{
    if (no == NULL)
    {
        return NULL;
    }
    // Movimentando
    if (LESS_THAN(cmp(elem, no->dado)))
    {
        no->esq = _remove_RBT(RB, no->esq, elem, cmp, removed);
        no = *removed ? _check_unbalanced(no, elem, cmp) : no;
        return no;
    }
    if (GREATER_THAN(cmp(elem, no->dado)))
    {
        no->dir = _remove_RBT(RB, no->dir, elem, cmp, removed);
        no = *removed ? _check_unbalanced(no, elem, cmp) : no;
        return no;
    }
    // Removendo
    *removed = true;
    if (no->dir == NULL && no->esq == NULL)
    {
        delete_NoTree(&no);
        RB->qtde--;
        return NULL;
    }
    if (no->dir == NULL && no->esq != NULL)
    {
        NoTree *esq = no->esq;
        delete_NoTree(&no);
        RB->qtde--;
        return esq;
    }
    if (no->dir != NULL && no->esq == NULL)
    {
        NoTree *dir = no->dir;
        delete_NoTree(&no);
        RB->qtde--;
        return dir;
    }

    NoTree *aux = _min_RBT(no->dir);

    copy_NoTree(no, aux);
    no->dir = _remove_RBT(RB, no->dir, no->dado, cmp, removed);
    return no;
}

void clear_RBT(RBT *RB)
{
    NoTree *_clear_RBT(NoTree * *no)
    {
        if (*no != NULL)
        {
            (*no)->esq = _clear_RBT(&((*no)->esq));
            (*no)->dir = _clear_RBT(&((*no)->dir));
            delete_NoTree(no);
        }
        return NULL;
    }
    RB->raiz = _clear_RBT(&(RB->raiz));
    RB->qtde = 0;
}

/* FUNCOES AUXILIARES */
bool empyt_RBT(RBT *RB)
{
    return RB->qtde == 0;
}
void in_order_RBT(RBT *RB, void (*print)(const void *))
{
    void _in_order_RBT(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            _in_order_RBT(no->esq, print);
            print_decorator_RBT(no->dado, print);
            _in_order_RBT(no->dir, print);
        }
    }
    printf("( ");
    _in_order_RBT(RB->raiz, print);
    printf(")");
}
void pre_order_RBT(RBT *RB, void (*print)(const void *))
{
    void _pre_order_RBT(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            print_decorator_RBT(no->dado, print);
            _pre_order_RBT(no->esq, print);
            _pre_order_RBT(no->dir, print);
        }
    }
    printf("( ");
    _pre_order_RBT(RB->raiz, print);
    printf(")");
}
void pos_order_RBT(RBT *RB, void (*print)(const void *))
{
    void _pos_order_RBT(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            _pos_order_RBT(no->esq, print);
            _pos_order_RBT(no->dir, print);
            print_decorator_RBT(no->dado, print);
        }
    }
    printf("( ");
    _pos_order_RBT(RB->raiz, print);
    printf(")");
}

static void print_decorator_RBT(const void *dado, void (*print)(const void *))
{
    print(dado);
    printf(" ");
}

int heigth_RBT(RBT *RB)
{
    return _heigth_RBT(RB->raiz);
}
static int _heigth_RBT(NoTree *no)
{
    if (no == NULL)
        return -1;
    int esq = _heigth_RBT(no->esq);
    int dir = _heigth_RBT(no->dir);
    return (dir > esq ? dir : esq) + 1;
}

static NoTree *_check_unbalanced(NoTree *no, void *elem, int (*cmp)(const void *, const void *))
{
    if (no)
    {
        if (no->esq && no->esq->cor == RED)
        {
            if (no->esq->esq && no->esq->esq->cor == RED)
                no = rotate_RR_RBT(no);
            if (no->esq->dir && no->esq->dir->cor == RED)
                no = rotate_RL_RBT(no);
        }
        if (no->dir && no->dir->cor == RED)
        {
            if (no->dir->dir && no->dir->dir->cor == RED)
                no = rotate_LL_RBT(no);
            if (no->dir->esq && no->dir->esq->cor == RED)
                no = rotate_LR_RBT(no);
        }
        if (no->esq && no->dir)
        {
            if (no->esq == RED && no->dir == RED)
            {
                if (no->esq->esq && no->esq->esq == RED)
                {
                    swap_color(no);
                }
                else if (no->esq->dir && no->esq->dir == RED)
                {
                    swap_color(no);
                }
                else if (no->dir->dir && no->dir->dir == RED)
                {
                    swap_color(no);
                }
                else if (no->dir->esq && no->dir->esq == RED)
                {
                    swap_color(no);
                }
            }
        }
    }
    return no;
}

static NoTree *rotate_RR_RBT(NoTree *no)
{
    NoTree *esq = no->esq;
    no->esq = esq->dir;
    esq->dir = no;
    esq->cor = no->cor;
    no->cor = RED;
    return esq;
}
static NoTree *rotate_LL_RBT(NoTree *no)
{
    NoTree *dir = no->dir;
    no->dir = dir->esq;
    dir->esq = no;
    dir->cor = no->cor;
    no->cor = RED;
    return dir;
}
static NoTree *rotate_RL_RBT(NoTree *no)
{
    no->esq = rotate_LL_RBT(no->esq);
    return rotate_RR_RBT(no);
}
static NoTree *rotate_LR_RBT(NoTree *no)
{
    no->dir = rotate_RR_RBT(no->dir);
    return rotate_LL_RBT(no);
}

void *min_RBT(RBT *RB)
{
    NoTree *aux = _min_RBT(RB->raiz);
    return aux == NULL ? NULL : aux->dado;
}
void *max_RBT(RBT *RB)
{
    NoTree *aux = _max_RBT(RB->raiz);
    return aux == NULL ? NULL : aux->dado;
}

static NoTree *_min_RBT(NoTree *no)
{
    if (no == NULL)
        return NULL;
    NoTree *aux = no;
    while (aux->esq != NULL)
        aux = aux->esq;
    return aux;
}
static NoTree *_max_RBT(NoTree *no)
{
    if (no == NULL)
        return NULL;
    NoTree *aux = no;
    while (aux->dir != NULL)
        aux = aux->dir;
    return aux;
}