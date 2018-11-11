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

/* CONSTRUTOR E DESTRUTOR */
ArrayList *new_ArrayList(size_t size, int length);                        // TODO
ArrayList *new_random_ArrayList(int begin, int end, int array_length);    // TODO
ArrayList *new_zeros_ArrayList(int array_length);                         // TODO
void realloc_ArrayList(ArrayList *ar, int length);                        // TODO
void delete_ArrayList(ArrayList **ar);                                    // TODO

/* FUNCOES DE BUSCA */
void *index_ArrayList(ArrayList *ar, int pos);                                             // TODO
int conteins_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
int find_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *));     // TODO

void *max_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO
void *min_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO

// Preciso pensar no caso das funcoes de insercao e remocao

/* FUNCOES DE INSERCAO */
int push_back_ArrayList(ArrayList *ar, void *elem);  // TODO
int push_front_ArrayList(ArrayList *ar, void *elem); // TODO

int insert_ArrayList(ArrayList *ar, void *elem, int pos); // TODO

int update_ArrayList(const ArrayList *dest, const ArrayList *font); // TODO

/* FUNCOES DE REMOCAO */
int pop_back_ArrayList(ArrayList *ar);         // TODO ---
int pop_front_ArrayList(ArrayList *ar);        // TODO
void *pop_back_data_ArrayList(ArrayList *ar);  // TODO
void *pop_front_data_ArrayList(ArrayList *ar); // TODO

int remove_ArrayList(ArrayList *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
int pop_ArrayList(ArrayList *ar, int pos);                                               // TODO
void remove_if_ArrayList(ArrayList *ar, int (*condicao)(void *));                        // TODO

void clear_ArrayList(ArrayList *ar); // TODO

/* FUNCOES AUXILIARES */
void print_ArrayList(ArrayList *ar, void (*print)(const void *));                                   // OK 03/08/2018
void print_if_ArrayList(ArrayList *ar, void (*print)(const void *), int (*condicao)(const void *)); // OK 03/08/2018

int is_sorted_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *));   // TODO
int is_reversed_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // TODO

void dup_ArrayList(ArrayList *fonte); // TODO

void unique_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // OK 03/08/2018

int empyt_ArrayList(ArrayList *ar); // OK 25/07/2018

void reverse_ArrayList(ArrayList *ar); // OK 03/08/2018

void *ArrayList_to_array(ArrayList *ar); // OK 03/08/2018

void swap_ArrayList(ArrayList *ar1, ArrayList *ar2); // OK 03/08/2018

int equals_ArrayList(ArrayList *ar1, ArrayList *ar2, int (*cmp)(const void *, const void *)); // OK 03/08/2018

/* FUNCOES DE ORDENACAO */
void sort_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *)); // 25/07/2018

/* IMPLEMENTACOES ArrayList */

/* CONSTRUTOR E DESTRUTOR */
ArrayList *new_ArrayList(size_t size, int length)
{
    ArrayList *ar = (ArrayList *)malloc(sizeof(ArrayList));

    ar->array = (void **)calloc(length, size);

    ar->qtde = 0;
    ar->length = length;
    ar->size = size;

    return ar;
}
void realloc_ArrayList(ArrayList *ar, int length) {}
void delete_ArrayList(ArrayList **ar) {}


/* FUNCOES AUXILIARES */
void print_ArrayList(ArrayList *ar, void (*print)(const void *))
{
    print_array(ar->array, ar->qtde, ar->size, print);
}

void print_if_ArrayList(ArrayList *ar, void (*print)(const void *), int (*condicao)(const void *))
{
    print_if_array(ar->array, ar->qtde, ar->size, print, condicao);
}

void unique_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *))
{
    unique_array(ar->array, ar->qtde, ar->size, cmp);
}

int empyt_ArrayList(ArrayList *ar)
{
    return ar->qtde == 0;
}

void reverse_ArrayList(ArrayList *ar)
{
    reverse_array(ar->array, ar->qtde, ar->size);
}

void *ArrayList_to_array(ArrayList *ar)
{
    return ar->array;
}

void swap_ArrayList(ArrayList *ar1, ArrayList *ar2)
{
    pswap(ar1->array, ar2->array);
    swap(&ar1->qtde, &ar2->qtde, sizeof(int));
    swap(&ar1->length, &ar2->length, sizeof(int));
    swap(&ar1->size, &ar2->size, sizeof(size_t));
}

int equals_ArrayList(ArrayList *ar1, ArrayList *ar2, int (*cmp)(const void *, const void *))
{
    if (ar1->qtde != ar2->qtde)
        return false;
    return equals_array(ar1->array, ar2->array, ar1->qtde, ar1->size, cmp);
}
/* FUNCOES DE ORDENACAO */
void sort_ArrayList(ArrayList *ar, int (*cmp)(const void *, const void *))
{
    qsort(ar->array, ar->qtde, ar->size, cmp);
}
#endif