// BST -> BinarySearchTree

#include "NoTree.h"
#include "tipos_primarios.h"

typedef struct BST
{
    NoTree *raiz;
    int qtde;
    size_t size;
} BST;

/* CONSTRUTOR E DESTRUTOR */
BST *new_BST(size_t size); // OK 30/07/2018
void delete_BST(BST **B);  // OK 30/07/2018

/* FUNCOES DE BUSCA */
NoTree *search_BST(BST *B, void *elem, int (*cmp)(const void *, const void *)); // OK 30/07/2018

/* FUNCOES DE INSERCAO */
void add_BST(BST *B, void *elem, int (*cmp)(const void *, const void *));                        // OK 30/07/2018
static NoTree *_add_BST(BST *B, NoTree *no, void *elem, int (*cmp)(const void *, const void *)); // OK 30/07/2018

/* FUNCOES DE REMOCAO */
void remove_BST(BST *B, void *elem, int (*cmp)(const void *, const void *));                        // OK 30/07/2018
static NoTree *_remove_BST(BST *B, NoTree *no, void *elem, int (*cmp)(const void *, const void *)); // OK 30/07/2018

void clear_BST(BST *L); // OK 30/07/2018

/* FUNCOES AUXILIARES */
bool empyt_BST(BST *B);                                                             // OK 30/07/2018
void in_order_BST(BST *B, void (*print)(const void *));                             // OK 30/07/2018
void pre_order_BST(BST *B, void (*print)(const void *));                            // OK 30/07/2018
void pos_order_BST(BST *B, void (*print)(const void *));                            // OK 30/07/2018
void copy_BST(BST *dest, const BST *fonte, int (*cmp)(const void *, const void *)); // OK 30/07/2018

static void print_decorator_BST(const void *dado, void (*print)(const void *)); // OK 30/07/2018

void *min_BST(BST *B);               // OK 30/07/2018
void *max_BST(BST *B);               // OK 30/07/2018
static NoTree *_min_BST(NoTree *no); // OK 30/07/2018
static NoTree *_max_BST(NoTree *no); // OK 30/07/2018

/* IMPLEMENTACOES BST */

/* CONSTRUTOR E DESTRUTOR */
BST *new_BST(size_t size)
{
    BST *B = (BST *)malloc(sizeof(BST));
    B->raiz = NULL;
    B->qtde = 0;
    B->size = size;
    return B;
}
void delete_BST(BST **B)
{
    clear_BST(*B);
    free(*B);
    *B = NULL;
}

/* FUNCOES DE BUSCA */
NoTree *search_BST(BST *B, void *elem, int (*cmp)(const void *, const void *))
{
    NoTree *_search_BST(NoTree * no, void *elem, int (*cmp)(const void *, const void *))
    {
        if (no == NULL)
            return NULL;
        if (cmp(elem, no->dado) > 0)
            return _search_BST(no->dir, elem, cmp);
        if (cmp(elem, no->dado) < 0)
            return _search_BST(no->esq, elem, cmp);
        return no;
    }
    return _search_BST(B->raiz, elem, cmp);
}

/* FUNCOES DE INSERCAO */
void add_BST(BST *B, void *elem, int (*cmp)(const void *, const void *))
{
    B->raiz = _add_BST(B, B->raiz, elem, cmp);
}
static NoTree *_add_BST(BST *B, NoTree *no, void *elem, int (*cmp)(const void *, const void *))
{
    if (no == NULL)
    {
        no = new_NoTree(elem, B->size);
        B->qtde++;
    }
    else if (cmp(elem, no->dado) < 0)
    {
        no->esq = _add_BST(B, no->esq, elem, cmp);
    }
    else if (cmp(elem, no->dado) > 0)
    {
        no->dir = _add_BST(B, no->dir, elem, cmp);
    }
    return no;
}

/* FUNCOES DE REMOCAO */
void remove_BST(BST *B, void *elem, int (*cmp)(const void *, const void *))
{
    B->raiz = _remove_BST(B, B->raiz, elem, cmp);
}
static NoTree *_remove_BST(BST *B, NoTree *no, void *elem, int (*cmp)(const void *, const void *))
{
    if (no == NULL)
    {
        return NULL;
    }
    // Movimentando
    if (LESS_THAN(cmp(elem, no->dado)))
    {
        no->esq = _remove_BST(B, no->esq, elem, cmp);
        return no;
    }
    if (GREATER_THAN(cmp(elem, no->dado)))
    {
        no->dir = _remove_BST(B, no->dir, elem, cmp);
        return no;
    }

    // Removendo
    if (no->dir == NULL && no->esq == NULL)
    {
        delete_NoTree(&no);
        B->qtde--;
        return NULL;
    }
    if (no->dir == NULL && no->esq != NULL)
    {
        NoTree *esq = no->esq;
        delete_NoTree(&no);
        B->qtde--;
        return esq;
    }
    if (no->dir != NULL && no->esq == NULL)
    {
        NoTree *dir = no->dir;
        delete_NoTree(&no);
        B->qtde--;
        return dir;
    }

    NoTree *aux = _min_BST(no->dir);

    copy_NoTree(no, aux);
    no->dir = _remove_BST(B, no->dir, no->dado, cmp);
    return no;
}

void clear_BST(BST *L)
{
    NoTree *_clear_BST(NoTree * *no)
    {
        if (*no != NULL)
        {
            (*no)->esq = _clear_BST(&((*no)->esq));
            (*no)->dir = _clear_BST(&((*no)->dir));
            delete_NoTree(no);
        }
        return NULL;
    }
    L->raiz = _clear_BST(&(L->raiz));
    L->qtde = 0;
}

/* FUNCOES AUXILIARES */
bool empyt_BST(BST *B)
{
    return B->qtde == 0;
}
void in_order_BST(BST *B, void (*print)(const void *))
{
    void _in_order_BST(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            _in_order_BST(no->esq, print);
            print_decorator_BST(no->dado, print);
            _in_order_BST(no->dir, print);
        }
    }
    printf("( ");
    _in_order_BST(B->raiz, print);
    printf(")");
}
void pre_order_BST(BST *B, void (*print)(const void *))
{
    void _pre_order_BST(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            print_decorator_BST(no->dado, print);
            _pre_order_BST(no->esq, print);
            _pre_order_BST(no->dir, print);
        }
    }
    printf("( ");
    _pre_order_BST(B->raiz, print);
    printf(")");
}
void pos_order_BST(BST *B, void (*print)(const void *))
{
    void _pos_order_BST(NoTree * no, void (*print)(const void *))
    {
        if (no != NULL)
        {
            _pos_order_BST(no->esq, print);
            _pos_order_BST(no->dir, print);
            print_decorator_BST(no->dado, print);
        }
    }
    printf("( ");
    _pos_order_BST(B->raiz, print);
    printf(")");
}
void copy_BST(BST *dest, const BST *fonte, int (*cmp)(const void *, const void *))
{
    void _copy_BST(BST * dest, NoTree * no, int (*cmp)(const void *, const void *))
    {
        if (no != NULL)
        {
            add_BST(dest, no->dado, cmp);
            _copy_BST(dest, no->esq, cmp);
            _copy_BST(dest, no->dir, cmp);
        }
    }
    if (dest->size == fonte->size)
        _copy_BST(dest, fonte->raiz, cmp);
}

static void print_decorator_BST(const void *dado, void (*print)(const void *))
{
    print(dado);
    printf(" ");
}

void *min_BST(BST *B)
{
    NoTree *aux = _min_BST(B->raiz);
    return aux == NULL ? NULL : aux->dado;
}
void *max_BST(BST *B)
{
    NoTree *aux = _max_BST(B->raiz);
    return aux == NULL ? NULL : aux->dado;
}
static NoTree *_min_BST(NoTree *no)
{
    if (no == NULL)
        return NULL;
    NoTree *aux = no;
    while (aux->esq != NULL)
        aux = aux->esq;
    return aux;
}
static NoTree *_max_BST(NoTree *no)
{
    if (no == NULL)
        return NULL;
    NoTree *aux = no;
    while (aux->dir != NULL)
        aux = aux->dir;
    return aux;
}