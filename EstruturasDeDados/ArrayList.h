#ifndef ARRAY_LIST
#define ARRAY_LIST

#include "../Util/tipos_primarios.h"
#include "../Util/array.h"

typedef struct arraylist
{
    void **array; // vetor de ponteiros
    int qtde;
    int length;
    size_t size;
} ArrayList;

/* FUNCOES DE BUSCA */
void *index_ArrayList(ArrayList *ar, int pos);                                             // TODO
int conteins_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
int find_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *));     // TODO

void *max_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO
void *min_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO

// Preciso pensar no caso das funcoes de insercao e remocao

/* FUNCOES DE INSERCAO */
int insert_ArrayList(ArrayList *ar, void *elem, int pos); // TODO

int update_ArrayList(const ArrayList *dest, const ArrayList *font); // TODO

/* FUNCOES DE REMOCAO */
int remove_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
int pop_ArrayList(ArrayList *ar, int pos);                                               // TODO
void remove_if_ArrayList(ArrayList *ar, int (*condicao)(void *));                        // TODO

/* FUNCOES AUXILIARES */
int is_sorted_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *));   // TODO
int is_reversed_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO

#endif