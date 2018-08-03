// Preciso pesar em como iterar sobre o array...

#ifndef ARRAYLIST
#define ARRAYLIST

#include "../Util/tipos_primarios.h"

typedef struct
{
    void **array; // vetor de ponteiros
    int qtde;
    int tam;
    size_t size;
} ArrayList;

/* CONSTRUTOR E DESTRUTOR */
ArrayList *new_ArrayList(size_t size, int tam);                        // TODO
ArrayList *new_random_ArrayList(int begin, int end, int array_length); // TODO
ArrayList *new_zeros_ArrayList(int array_length);                      // TODO
void realloc_ArrayList(ArrayList *ar, int tam);                        // TODO
void delete_ArrayList(ArrayList **ar);                                 // TODO

/* FUNCOES DE BUSCA */
void *index_ArrayList(ArrayList *ar, int pos);                                              // TODO
bool conteins_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
int find_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *));      // TODO

void *max_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO
void *min_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO

// Preciso pensar no caso das funcoes de insercao e remocao

/* FUNCOES DE INSERCAO */
bool push_back_ArrayList(ArrayList *ar, void *elem);  // TODO
bool push_front_ArrayList(ArrayList *ar, void *elem); // TODO

bool insert_ArrayList(ArrayList *ar, void *elem, int pos); // TODO

bool update_ArrayList(const ArrayList *dest, const ArrayList *font); // TODO

/* FUNCOES DE REMOCAO */
bool pop_back_ArrayList(ArrayList *ar);        // TODO
bool pop_front_ArrayList(ArrayList *ar);       // TODO
void *pop_back_dado_ArrayList(ArrayList *ar);  // TODO
void *pop_front_dado_ArrayList(ArrayList *ar); // TODO

bool remove_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
bool pop_ArrayList(ArrayList *ar, int pos);                                               // TODO
void remove_if_ArrayList(ArrayList *ar, bool (*condicao)(void *));                        // TODO

void clear_ArrayList(ArrayList *ar); // TODO

/* FUNCOES AUXILIARES */
void print_ArrayList(ArrayList *ar, void (*print)(const void *));                                    // TODO
void print_if_ArrayList(ArrayList *ar, void (*print)(const void *), bool (*condicao)(const void *)); // TODO

bool is_sorted_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *));   // TODO
bool is_reversed_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO

double sum_ArrayList(ArrayList *ar, double (*cast)(const void *));  // TODO
double mult_ArrayList(ArrayList *ar, double (*cast)(const void *)); // TODO

void copy_ArrayList(ArrayList *dest, const ArrayList *fonte); // TODO

void unique_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO

bool empyt_ArrayList(ArrayList *ar); // 25/07/2018

void reverse_ArrayList(ArrayList *ar); // TODO

void *ArrayList_to_array(ArrayList *ar); // TODO

void swap_ArrayList(ArrayList *ar1, ArrayList *ar2); // 25/07/2018

bool equals_ArrayList(ArrayList *ar1, ArrayList *ar2); // TODO

/* FUNCOES DE ORDENACAO */
void sort_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // 25/07/2018

/* IMPLEMENTACOES ARRAYLIST */

/* CONSTRUTOR E DESTRUTOR */
ArrayList *new_ArrayList(size_t size, int tam)
{
    ArrayList *ar = (ArrayList *)malloc(sizeof(ArrayList));

    ar->dado = (void **)calloc(tam, size);

    ar->qtde = 0;
    ar->tam = tam;
    ar->size = size;

    return ar;
}
void realloc_ArrayList(ArrayList *ar, int tam) {}
void delete_ArrayList(ArrayList **ar) {}

/* FUNCOES AUXILIARES */
bool empyt_ArrayList(ArrayList *ar)
{
    return ar->qtde == 0;
}

void swap_ArrayList(ArrayList *ar1, ArrayList *ar2)
{
    swap(ar1->array, ar2->array, sizeof(void **));
    swap(ar1->qtde, ar2->qtde, sizeof(int));
    swap(ar1->tam, ar2->tam, sizeof(int));
    swap(ar1->size, ar2->size, sizeof(size_t));
}

/* FUNCOES DE ORDENACAO */
void sort_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *))
{
    qsort(ar->array, ar->qtde, ar->size, cmp);
}
#endif