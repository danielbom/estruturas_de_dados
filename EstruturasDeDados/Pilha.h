/*

Pilhas são estruturas de dados utilizadas para simular algumas situações reais.

Todas as funções foram testadas pelo menor uma vez.

*/

#include "NoSent.h"

typedef struct
{
    NoSent *Topo;
    int tam;
    size_t size;
} Pilha;

/* CONSTRUTOR E DESTRUTOR */
Pilha *new_Pilha(size_t size); // OK
void delete_Pilha(Pilha **P);  // OK

/* FUNCOES DE INSERCAO */
NoSent *push_Pilha(Pilha *P, void *elem);                         // OK
static NoSent *push_ant_Pilha(Pilha *P, void *elem, NoSent *pos); // OK

/* FUNCOES DE REMOCAO */
NoSent *pop_Pilha(Pilha *P);                        // OK
static NoSent *pop_in_Pilha(Pilha *P, NoSent *pos); // OK

void clear_Pilha(Pilha *P); // OK

/* FUNCOES AUXILIARES */
void reverse_Pilha(Pilha **P);                           // OK
void copy_Pilha(Pilha *dest, const Pilha *fonte);        // OK
void swap_Pilha(Pilha *P1, Pilha *P2);                   // OK
void print_Pilha(Pilha *P, void (*print)(const void *)); // OK

/* IMPLEMENTACOES PILHA */
Pilha *new_Pilha(size_t size)
{
    Pilha *P = (Pilha *)malloc(sizeof(Pilha));

    void *aux = calloc(1, size);
    P->Topo = new_NoSent(aux, size);
    free(aux);

    P->Topo->prox = P->Topo->ant = P->Topo;

    P->tam = 0;
    P->size = size;

    return P;
}
void delete_Pilha(Pilha **P)
{
    clear_Pilha(*P);
    delete_NoSent(&((*P)->Topo));
    free(*P);
    *P = NULL;
}

NoSent *push_Pilha(Pilha *P, void *elem)
{
    return push_ant_Pilha(P, elem, P->Topo);
}

static NoSent *push_ant_Pilha(Pilha *P, void *elem, NoSent *pos)
{
    // assert(L != NULL);
    if (pos == NULL)
        return NULL;
    if (elem == NULL)
        return NULL;
    if (P == NULL)
        return NULL;

    NoSent *novo = new_NoSent(elem, P->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    P->tam++;

    return novo;
}

NoSent *pop_Pilha(Pilha *P)
{
    return pop_in_Pilha(P, P->Topo->prox);
}

static NoSent *pop_in_Pilha(Pilha *P, NoSent *pos)
{
    // assert(L != NULL);
    // assert(pos != NULL);
    // assert(pos != L->Sentinela);
    if (P == NULL)
        return NULL;
    if (pos == NULL)
        return NULL;
    if (pos == P->Topo)
        return NULL;

    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    pos->prox = pos->ant = NULL;

    P->tam--;

    return pos;
}

void clear_Pilha(Pilha *P)
{
    NoSent *aux = pop_Pilha(P);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_Pilha(P);
    }
}

void reverse_Pilha(Pilha **P)
{
    NoSent *aux = pop_Pilha(*P);
    Pilha *T = new_Pilha((*P)->size);
    while (aux != NULL)
    {
        push_ant_Pilha(T, aux->dado, T->Topo);
        delete_NoSent(&aux);
        aux = pop_Pilha(*P);
    }
    delete_Pilha(P);
    *P = T;
}

void copy_Pilha(Pilha *dest, const Pilha *fonte)
{
    if (dest == NULL || fonte == NULL)
        return;
    if (dest->size != fonte->size)
        return;
    if (dest->tam != 0)
    {
        clear_Pilha(dest);
    }
    NoSent *aux = fonte->Topo->ant;
    while (aux != fonte->Topo)
    {
        push_Pilha(dest, aux->dado);
        aux = aux->ant;
    }
}

void swap_Pilha(Pilha *P1, Pilha *P2)
{
    if (P1 == NULL || P2 == NULL)
        return;
    if (P1->size != P2->size)
        return;
    Pilha *aux = new_Pilha(P1->size);
    copy_Pilha(aux, P1);
    copy_Pilha(P1, P2);
    copy_Pilha(P2, aux);
}

void print_Pilha(Pilha *P, void (*print)(const void *))
{
    NoSent *aux = P->Topo->prox;
    while (aux != P->Topo)
    {
        print(aux->dado);
        aux = aux->prox;
    }
}
