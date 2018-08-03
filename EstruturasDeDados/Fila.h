/*

Filas são estruturas de dados utilizadas para simular algumas situações reais.

Todas as funções foram testadas pelo menor uma vez.

*/

#include "NoSent.h"

typedef struct
{
    NoSent *Topo;
    int tam;
    size_t size;
} Fila;

/* CONSTRUTOR E DESTRUTOR */
Fila *new_Fila(size_t size); // OK
void delete_Fila(Fila **F);  // OK

/* FUNCOES DE INSERCAO */
NoSent *push_Fila(Fila *F, void *elem);                         // OK
static NoSent *push_ant_Fila(Fila *F, void *elem, NoSent *pos); // OK

/* FUNCOES DE REMOCAO */
NoSent *pop_Fila(Fila *F);                        // OK
static NoSent *pop_in_Fila(Fila *F, NoSent *pos); // OK

void clear_Fila(Fila *F); // OK

/* FUNCOES AUXILIARES */
void reverse_Fila(Fila **F);                           // OK
void copy_Fila(Fila *dest, const Fila *fonte);         // OK
void swap_Fila(Fila *F1, Fila *F2);                    // OK
void print_Fila(Fila *F, void (*print)(const void *)); // OK

/* IMPLEMENTACOES Fila */
Fila *new_Fila(size_t size)
{
    Fila *F = (Fila *)malloc(sizeof(Fila));

    void *aux = calloc(1, size);
    F->Topo = new_NoSent(aux, size);
    free(aux);

    F->Topo->prox = F->Topo->ant = F->Topo;

    F->tam = 0;
    F->size = size;

    return F;
}
void delete_Fila(Fila **F)
{
    clear_Fila(*F);
    delete_NoSent(&((*F)->Topo));
    free(*F);
    *F = NULL;
}

NoSent *push_Fila(Fila *F, void *elem)
{
    return push_ant_Fila(F, elem, F->Topo);
}

static NoSent *push_ant_Fila(Fila *F, void *elem, NoSent *pos)
{
    // assert(L != NULL);
    if (pos == NULL)
        return NULL;
    if (elem == NULL)
        return NULL;
    if (F == NULL)
        return NULL;

    NoSent *novo = new_NoSent(elem, F->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    F->tam++;

    return novo;
}

NoSent *pop_Fila(Fila *F)
{
    return pop_in_Fila(F, F->Topo->ant);
}

static NoSent *pop_in_Fila(Fila *F, NoSent *pos)
{
    // assert(L != NULL);
    // assert(pos != NULL);
    // assert(pos != L->Sentinela);
    if (F == NULL)
        return NULL;
    if (pos == NULL)
        return NULL;
    if (pos == F->Topo)
        return NULL;

    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    pos->prox = pos->ant = NULL;

    F->tam--;

    return pos;
}

void clear_Fila(Fila *F)
{
    NoSent *aux = pop_Fila(F);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_Fila(F);
    }
}

void reverse_Fila(Fila **F)
{
    NoSent *aux = pop_Fila(*F);
    Fila *T = new_Fila((*F)->size);
    while (aux != NULL)
    {
        push_ant_Fila(T, aux->dado, T->Topo->ant);
        delete_NoSent(&aux);
        aux = pop_Fila(*F);
    }
    delete_Fila(F);
    *F = T;
}

void copy_Fila(Fila *dest, const Fila *fonte)
{
    if (dest == NULL || fonte == NULL)
        return;
    if (dest->size != fonte->size)
        return;
    if (dest->tam != 0)
    {
        clear_Fila(dest);
    }
    NoSent *aux = fonte->Topo->ant;
    while (aux != fonte->Topo)
    {
        push_Fila(dest, aux->dado);
        aux = aux->ant;
    }
}

void swap_Fila(Fila *F1, Fila *F2)
{
    if (F1 == NULL || F2 == NULL)
        return;
    if (F1->size != F2->size)
        return;
    Fila *aux = new_Fila(F1->size);
    copy_Fila(aux, F1);
    copy_Fila(F1, F2);
    copy_Fila(F2, aux);
}

void print_Fila(Fila *F, void (*print)(const void *))
{
    NoSent *aux = F->Topo->prox;
    while (aux != F->Topo)
    {
        print(aux->dado);
        aux = aux->prox;
    }
}
