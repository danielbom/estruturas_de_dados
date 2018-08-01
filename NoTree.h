#ifndef NOTREE
#define NOTREE

#include <stdbool.h>

#define BLACK true
#define RED false

typedef struct NoTree
{
    void *dado;
    size_t size;
    bool cor;
    struct NoTree *dir;
    struct NoTree *esq;
} NoTree;

/* FUNCOES DO NO */
NoTree *new_NoTree(void *elem, size_t s);            // OK 30/07/2018
void copy_NoTree(NoTree *dest, const NoTree *fonte); // OK 30/07/2018
void swap_NoTree(NoTree *a, NoTree *b);              // OK 30/07/2018
void delete_NoTree(NoTree **no);                     // OK 18/06/2018
void swap_color(NoTree *no);                         // OK 31/07/2018

/* IMPLEMENTACAO NO */
NoTree *new_NoTree(void *elem, size_t s)
{
    NoTree *novo = (NoTree *)calloc(1, sizeof(NoTree));

    novo->dir = novo->esq = NULL;

    novo->dado = calloc(1, s);
    memcpy(novo->dado, elem, s);

    novo->size = s;
    novo->cor = false;

    return novo;
}
void copy_NoTree(NoTree *dest, const NoTree *fonte)
{
    memcpy(dest->dado, fonte->dado, fonte->size);
    dest->size = fonte->size;
    dest->cor = fonte->cor;
}
void swap_NoTree(NoTree *a, NoTree *b)
{
    void *tmp = a->dado;
    a->dado = b->dado;
    b->dado = tmp;
}
void delete_NoTree(NoTree **no)
{
    free((*no)->dado);
    free(*no);
}

void swap_color(NoTree *no)
{
    no->cor = !no->cor;
    if (no->esq)
        no->esq->cor = !no->esq->cor;
    if (no->dir)
        no->dir->cor = !no->dir->cor;
}

#endif