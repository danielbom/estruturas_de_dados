// RBT -> Red-Black Tree

#include "tipos_primarios.h"
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
bool add_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *));                                                // TODO
static NoTree *_add_RBT(RBT *RB, NoTree *no, NoTree *pai, void *elem, int (*cmp)(const void *, const void *), bool *add); // TODO

/* FUNCOES DE REMOCAO */
bool remove_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *));                                                    // TODO
static NoTree *_remove_RBT(RBT *RB, NoTree *no, NoTree *pai, void *elem, int (*cmp)(const void *, const void *), bool *removed); // TODO

void clear_RBT(RBT *RB); // OK 30/07/2018

/* FUNCOES AUXILIARES */
bool empyt_RBT(RBT *RB);                                  // OK 30/07/2018
void in_order_RBT(RBT *RB, void (*print)(const void *));  // OK 30/07/2018
void pre_order_RBT(RBT *RB, void (*print)(const void *)); // OK 30/07/2018
void pos_order_RBT(RBT *RB, void (*print)(const void *)); // OK 30/07/2018

static void print_decorator_RBT(const void *dado, void (*print)(const void *)); // OK 30/07/2018

int heigth_RBT(RBT *RB);                  // OK 30/07/2018
static int _heigth_RBT(NoTree *no);       // OK 30/07/2018
static int _heigth_black_RBT(NoTree *no); // OK ?

static NoTree *_check_remove(NoTree *no, NoTree *pai, void *elem, int (*cmp)(const void *, const void *));
static NoTree *_check_add(NoTree *no, NoTree *pai, void *elem, int (*cmp)(const void *, const void *));
static NoTree *_check_colors_remove(NoTree *no, NoTree *pai);
static NoTree *_check_colors_add(NoTree *no, NoTree *pai);
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
    RBT *RB = (RBT *)malloc(sizeof(RBT));
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
        if (cmp(elem, no->dado) > 0)
            return _search_RBT(no->dir, elem, cmp);
        if (cmp(elem, no->dado) < 0)
            return _search_RBT(no->esq, elem, cmp);
        return no;
    }
    return _search_RBT(RB->raiz, elem, cmp);
}

/* FUNCOES DE INSERCAO */
bool add_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *))
{
    bool _add = false;
    if (RB->raiz == NULL)
    {
        RB->raiz = new_NoTree(elem, RB->size);
        RB->raiz->cor = true;
    }
    else
    {
        RB->raiz = _add_RBT(RB, RB->raiz, NULL, elem, cmp, &_add);
    }
    return _add;
}
static NoTree *_add_RBT(RBT *RB, NoTree *no, NoTree *pai, void *elem, int (*cmp)(const void *, const void *), bool *add)
{
}
/* FUNCOES DE REMOCAO */
bool remove_RBT(RBT *RB, void *elem, int (*cmp)(const void *, const void *))
{
    bool _removed = false;
    RB->raiz = _remove_RBT(RB, RB->raiz, NULL, elem, cmp, &_removed);
    return _removed;
}
static NoTree *_remove_RBT(RBT *RB, NoTree *no, NoTree *pai, void *elem, int (*cmp)(const void *, const void *), bool *removed)
{
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
static int _heigth_black_RBT(NoTree *no)
{
    if (no == NULL)
        return 1;
    int esq = _heigth_black_RBT(no->esq);
    int dir = _heigth_black_RBT(no->dir);
    return (dir > esq ? dir : esq) + is_black(no);
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