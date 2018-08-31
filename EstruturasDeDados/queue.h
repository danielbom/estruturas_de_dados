/*

Filas(queue) são estruturas de dados utilizadas para simular algumas situações reais.

*/

#include "NoSent.h"

typedef struct
{
    NoSent *Topo;
    int tam;
    size_t size;
} queue;

/* CONSTRUTOR E DESTRUTOR */
queue *new_queue(size_t size); // OK
void delete_queue(queue **F);  // OK

/* FUNCOES DE INSERCAO */
NoSent *push_queue(queue *F, void *elem);                         // OK
static NoSent *push_ant_queue(queue *F, void *elem, NoSent *pos); // OK

/* FUNCOES DE REMOCAO */
NoSent *pop_queue(queue *F);                        // OK
static NoSent *pop_in_queue(queue *F, NoSent *pos); // OK

void clear_queue(queue *F); // OK

/* FUNCOES AUXILIARES */
void reverse_queue(queue **F);                                 // OK
void copy_queue(queue *dest, const queue *fonte);              // OK
void swap_queue(queue *F1, queue *F2);                         // OK
void print_queue(const queue *F, void (*print)(const void *)); // OK
bool is_empty_queue(const queue *F);

/* IMPLEMENTACOES queue */
queue *new_queue(size_t size)
{
    if (SizeError(size, "new_queue"))
        return NULL;
    queue *F = (queue *)malloc(sizeof(queue));
    F->Topo = create_Sent();
    F->tam = 0;
    F->size = size;
    return F;
}
void delete_queue(queue **F)
{
    if (NullPointerError(F, "delete_queue"))
        return;
    if (NullPointerError(*F, "delete_queue"))
        return;
    clear_queue(*F);
    delete_NoSent(&((*F)->Topo));
    free(*F);
    *F = NULL;
}

NoSent *push_queue(queue *F, void *elem)
{
    return push_ant_queue(F, elem, F->Topo);
}

static NoSent *push_ant_queue(queue *F, void *elem, NoSent *pos)
{
    if (NullPointerError(F, "delete_queue"))
        return NULL;
    if (NullPointerError(elem, "delete_queue"))
        return NULL;
    if (NullPointerError(pos, "delete_queue"))
        return NULL;

    NoSent *novo = new_NoSent(elem, F->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    F->tam++;

    return novo;
}

NoSent *pop_queue(queue *F)
{
    return pop_in_queue(F, F->Topo->ant);
}

static NoSent *pop_in_queue(queue *F, NoSent *pos)
{
    if (NullPointerError(F, "delete_queue"))
        return NULL;
    if (NullPointerError(pos, "delete_queue"))
        return NULL;
    if (is_empty_queue(F))
        return NULL;

    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    pos->prox = pos->ant = NULL;

    F->tam--;

    return pos;
}

void clear_queue(queue *F)
{
    if (NullPointerError(F, "clear_queue"))
        return;
    NoSent *aux = pop_queue(F);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_queue(F);
    }
}

void reverse_queue(queue **F)
{
    if (NullPointerError(F, "reverse_queue"))
        return;
    if (NullPointerError(*F, "reverse_queue"))
        return;
    NoSent *aux = pop_queue(*F);
    queue *T = new_queue((*F)->size);
    while (aux != NULL)
    {
        push_ant_queue(T, aux->dado, T->Topo->ant);
        delete_NoSent(&aux);
        aux = pop_queue(*F);
    }
    delete_queue(F);
    *F = T;
}

void copy_queue(queue *dest, const queue *fonte)
{
    if (NullPointerError(dest, "copy_queue"))
        return;
    if (NullPointerError(font, "copy_queue"))
        return;

    if (dest->tam != 0)
        clear_queue(dest);

    NoSent *aux = fonte->Topo->ant;
    while (aux != fonte->Topo)
    {
        push_queue(dest, aux->dado);
        aux = aux->ant;
    }
    dest->size = fonte->size;
}

void swap_queue(queue *F1, queue *F2)
{
    if (NullPointerError(dest, "swap_queue"))
        return;
    if (NullPointerError(font, "swap_queue"))
        return;
    if (F1->size != F2->size)
        return;
    queue *aux = new_queue(F1->size);
    copy_queue(aux, F1);
    copy_queue(F1, F2);
    copy_queue(F2, aux);
}

void print_queue(queue *F, void (*print)(const void *))
{
    if (NullPointerError(F, "print_queue"))
        return;
    NoSent *aux = F->Topo->prox;
    printf("( ");
    while (aux != F->Topo)
    {
        print(aux->dado);
        printf(", ");
        aux = aux->prox;
    }
    printf(")");
}

bool is_empty_queue(const queue *F)
{
    if (NullPointerError(F, "is_empty_queue"))
        return;
    return F->tam == 0;
}