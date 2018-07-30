/*

Listas são estruturas de dados que não é boa com buscas.
Se precisas fazer muitas buscas, utilize outra estrutura de dados.

Funções testadas pelo menos uma vez.

CONSTRUTOR E DESTRUTOR
todas

FUNCOES DE BUSCA
(--) nenhuma

FUNCOES DE INSERCAO
(+-) todas, exceto insert_Lista

FUNCOES DE REMOCAO
(+-) todas, exceto pop_Lista

FUNCOES AUXILIARES
(++) todas

FUNCOES DE ORDENACAO
(++) todas

*/
#ifndef LISTA
#define LISTA

#include "tipos_primarios.h"
#include "NoSent.h"

typedef struct
{
    NoSent *Sentinela;
    int qtde;
    size_t size;
} Lista;

/* CONSTRUTOR E DESTRUTOR */
Lista *new_Lista(size_t size);                                     // OK 18/06/2018
Lista *array_to_Lista(void *array, int length_array, size_t size); // OK 17/07/2018
void delete_Lista(Lista **L);                                      // OK 18/07/2018

/* FUNCOES DE BUSCA */
void *index_Lista(Lista *L, int pos);      // OK 24/06/2018
NoSent *index_no_Lista(Lista *L, int pos); // OK 18/06/2018

bool conteins_Lista(Lista *L, void *elem, int (*cmp)(const void *, const void *));     // OK 24/06/2018
NoSent *search_no_Lista(Lista *L, void *elem, int (*cmp)(const void *, const void *)); // OK 24/06/2018

void *max_Lista(Lista *L, int (*cmp)(const void *, const void *));      // OK 18/07/2018
void *min_Lista(Lista *L, int (*cmp)(const void *, const void *));      // OK 18/07/2018
NoSent *max_no_Lista(Lista *L, int (*cmp)(const void *, const void *)); // OK 18/07/2018
NoSent *min_no_Lista(Lista *L, int (*cmp)(const void *, const void *)); // OK 18/07/2018

/* FUNCOES DE INSERCAO */
NoSent *push_no_Lista(Lista *L, void *elem, NoSent *pos); // OK 18/06/2018
bool push_back_Lista(Lista *L, void *elem);               // OK 18/06/2018
bool push_front_Lista(Lista *L, void *elem);              // OK 18/06/2018

bool insert_Lista(Lista *L, void *elem, int pos); // OK 18/06/2018

bool update_Lista(Lista *dest, const Lista *font);

/* FUNCOES DE REMOCAO */
NoSent *pop_in_Lista(Lista *L, NoSent *pos); // OK 18/06/2018
NoSent *pop_back_no_Lista(Lista *L);         // OK 24/06/2018
NoSent *pop_front_no_Lista(Lista *L);        // OK 24/06/2018
bool pop_back_Lista(Lista *L);               // OK 24/06/2018
bool pop_front_Lista(Lista *L);              // OK 24/06/2018
void *pop_back_dado_Lista(Lista *L);         // OK 24/06/2018
void *pop_front_dado_Lista(Lista *L);        // OK 24/06/2018

bool remove_Lista(Lista *L, void *elem, int (*cmp)(const void *, const void *)); // OK 24/06/2018
bool pop_Lista(Lista *L, int pos);                                               // OK 18/06/2018
void remove_if_Lista(Lista *L, bool (*condicao)(void *));                        // OK 18/06/2018

void clear_Lista(Lista *L); // OK 18/06/2018

/* FUNCOES AUXILIARES */
void copy_Lista(Lista *dest, const Lista *fonte);                         // OK 18/06/2018
void swap_Lista(Lista *L1, Lista *L2);                                    // OK 18/07/2018
void print_Lista(Lista *L, void (*print)(const void *));                  // OK 18/06/2018
bool empyt_Lista(Lista *L);                                               // OK 18/07/2018
void unique_Lista(Lista *L, int (*cmp)(const void *, const void *));      // OK 17/07/2018
bool is_sorted_Lista(Lista *L, int (*cmp)(const void *, const void *));   // OK 22/07/2018
bool is_reversed_Lista(Lista *L, int (*cmp)(const void *, const void *)); // OK 22/07/2018
void reverse_Lista(Lista *L);                                             // OK 17/07/2018
void *Lista_to_array(Lista *L);                                           // OK 17/07/2018
bool equals_Lista(const Lista *a, const Lista *b);                        // TODO

double sum_Lista(Lista *L, double (*cast)(const void *));  // TODO
double mult_Lista(Lista *L, double (*cast)(const void *)); // TODO

NoSent *begin_Lista(Lista *L);     // OK 17/07/2018
NoSent *end_Lista(Lista *L);       // OK 17/07/2018
void next_iter_Lista(NoSent **no); // OK 17/07/2018

/* FUNCOES DE ORDENACAO */
void sort_Lista(Lista *L, int (*cmp)(const void *, const void *));                                            // OK 17/07/2018
static void _quick_sort_Lista(Lista *L, NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *)); // OK 17/07/2018
static NoSent *_partition_Lista(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *));         // OK 17/07/2018
static NoSent *_partition_Lista2(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *));

/* IMPLEMENTACOES LISTA */

/* CONSTRUTOR E DESTRUTOR */
Lista *new_Lista(size_t size)
{
    assert(size > 0);

    Lista *L = (Lista *)malloc(sizeof(Lista));

    void *aux = calloc(1, size);
    L->Sentinela = new_NoSent(calloc(1, size), size);
    free(aux);

    L->Sentinela->ant = L->Sentinela->prox = L->Sentinela;

    L->qtde = 0;
    L->size = size;

    return L;
}
Lista *array_to_Lista(void *array, int length_array, size_t size)
{
    assert(array != NULL);
    assert(length_array > 0);
    assert(size > 0);

    Lista *L = new_Lista(size);
    void *it = array;
    for (int i = 0; i < length_array; i++)
    {
        push_back_Lista(L, array + i * size);
    }
    return L;
}

Lista *new_random_int_Lista(int begin, int end, int array_length)
{
    if (begin > end)
        swap(&begin, &end, sizeof(int));

    Lista *L = new_Lista(sizeof(int));

    int range = end - begin;
    int *a;
    srand((unsigned)time(NULL));
    for (int i = 0; i < array_length; i++)
    {
        a = (int *)malloc(sizeof(int));
        *a = (rand() % range) + begin;
        push_back_Lista(L, a);
    }

    return L;
}

void delete_Lista(Lista **L)
{
    assert(*L != NULL);

    clear_Lista(*L);
    delete_NoSent(&((*L)->Sentinela));
    free(*L);
    *L = NULL;
}

/* FUNCOES DE BUSCA */
NoSent *index_no_Lista(Lista *L, int pos)
{
    assert(L != NULL);

    if (pos > L->qtde)
        return NULL;
    if (L->qtde == 0)
        return NULL;
    if (pos < 0)
        pos += L->qtde + 1;

    NoSent *aux;
    int i;
    if (pos > L->qtde / 2)
    {
        aux = L->Sentinela->ant;
        for (i = L->qtde; i > pos; i--)
            aux = aux->ant;
    }
    else
    {
        aux = L->Sentinela->prox;
        for (i = 1; i < pos; i++)
            aux = aux->prox;
    }
    return aux;
}
void *index_Lista(Lista *L, int pos)
{
    NoSent *aux = index_Lista(L, pos);
    if (aux != NULL)
    {
        return aux->dado;
    }
    return NULL;
}

NoSent *search_no_Lista(Lista *L, void *elem, int (*cmp)(const void *, const void *))
{
    assert(L != NULL);

    NoSent *aux = L->Sentinela->prox;
    while (aux != L->Sentinela)
    {
        if (EQUAL_TO(cmp(elem, aux->dado)))
            return aux;
        aux = aux->prox;
    }
    return NULL;
}
bool conteins_Lista(Lista *L, void *elem, int (*cmp)(const void *, const void *))
{
    NoSent *aux = search_no_Lista(L, elem, cmp);
    return aux != NULL;
}

NoSent *max_no_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    assert(L != NULL);

    NoSent *aux = L->Sentinela->prox;
    NoSent *max = L->Sentinela->prox;
    while (aux != L->Sentinela)
    {
        if (GREATER_THAN(cmp(aux->dado, max->dado)))
            max = aux;
        aux = aux->prox;
    }
    return max;
}
void *max_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    NoSent *aux = max_no_Lista(L, cmp);
    if (aux != NULL)
    {
        return aux->dado;
    }
    return NULL;
}

NoSent *min_no_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    assert(L != NULL);

    NoSent *aux = L->Sentinela->prox;
    NoSent *min = L->Sentinela->prox;
    while (aux != L->Sentinela)
    {
        if (LESS_THAN(cmp(min->dado, aux->dado)))
            min = aux;
        aux = aux->prox;
    }
    return min;
}
void *min_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    NoSent *aux = min_no_Lista(L, cmp);
    if (aux != NULL)
    {
        return aux->dado;
    }
    return NULL;
}

/* FUNCOES DE INSERCAO */
NoSent *push_no_Lista(Lista *L, void *elem, NoSent *pos)
{
    // Coloca o elemento 'elem' apos o no 'pos' na lista 'L'
    assert(L != NULL);

    if (pos == NULL)
        return NULL;

    NoSent *novo = new_NoSent(elem, L->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    L->qtde++;

    return novo;
}
bool push_back_Lista(Lista *L, void *elem)
{
    return push_no_Lista(L, elem, L->Sentinela->ant) != NULL;
}
bool push_front_Lista(Lista *L, void *elem)
{
    return push_no_Lista(L, elem, L->Sentinela) != NULL;
}

bool insert_Lista(Lista *L, void *elem, int pos)
{
    NoSent *index = index_no_Lista(L, pos);
    if (index != NULL)
    {
        NoSent *aux = push_no_Lista(L, elem, index);
        return aux != NULL;
    }
    return false;
}

bool update_Lista(Lista *dest, const Lista *font)
{
    assert(dest != NULL && font != NULL);
    assert(dest->size == font->size);

    NoSent *aux = font->Sentinela->prox;
    while (aux != font->Sentinela)
    {
        push_back_Lista(dest, aux->dado);
        aux = aux->prox;
    }
}

/* FUNCOES DE REMOCAO */
NoSent *pop_in_Lista(Lista *L, NoSent *pos)
{
    assert(L != NULL);

    if (pos == NULL)
        return NULL;
    if (pos == L->Sentinela)
        return NULL;

    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    pos->prox = pos->ant = NULL;

    L->qtde--;

    return pos;
}

NoSent *pop_back_no_Lista(Lista *L)
{
    return pop_in_Lista(L, L->Sentinela->ant);
}
bool pop_back_Lista(Lista *L)
{
    NoSent *aux = pop_back_no_Lista(L);
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void *pop_back_dado_Lista(Lista *L)
{
    NoSent *aux = pop_back_no_Lista(L);
    if (aux != NULL)
    {
        void *dado = malloc(aux->size);
        memcpy(dado, aux->dado, aux->size);
        delete_NoSent(&aux);
        return dado;
    }
    return NULL;
}

NoSent *pop_front_no_Lista(Lista *L)
{
    return pop_in_Lista(L, L->Sentinela->prox);
}
bool pop_front_Lista(Lista *L)
{
    NoSent *aux = pop_front_no_Lista(L);
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void *pop_front_dado_Lista(Lista *L)
{
    NoSent *aux = pop_front_no_Lista(L);
    if (aux != NULL)
    {
        void *dado = malloc(aux->size);
        memcpy(dado, aux->dado, aux->size);
        delete_NoSent(&aux);
        return dado;
    }
    return NULL;
}
bool remove_Lista(Lista *L, void *elem, int (*cmp)(const void *, const void *))
{
    NoSent *aux = pop_in_Lista(L, search_no_Lista(L, elem, cmp));
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
bool pop_Lista(Lista *L, int pos)
{
    NoSent *aux = pop_in_Lista(L, index_no_Lista(L, pos));
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void remove_if_Lista(Lista *L, bool (*condicao)(void *))
{
    assert(L != NULL);

    NoSent *aux = L->Sentinela->prox;
    while (aux != L->Sentinela)
    {
        if (condicao(aux->dado))
        {
            NoSent *tmp = aux->prox;
            aux = pop_in_Lista(L, aux);
            delete_NoSent(&aux);
            aux = tmp;
        }
        else
        {
            aux = aux->prox;
        }
    }
}

void clear_Lista(Lista *L)
{
    assert(L != NULL);

    NoSent *aux = pop_back_no_Lista(L);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_back_no_Lista(L);
    }
}

/* FUNCOES AUXILIARES */
void copy_Lista(Lista *dest, const Lista *font)
{
    assert(dest != NULL && font != NULL);

    if (dest->size != font->size)
        return;
    if (dest->qtde != 0)
        clear_Lista(dest);

    NoSent *aux = font->Sentinela->prox;
    while (aux != font->Sentinela)
    {
        push_back_Lista(dest, aux->dado);
        aux = aux->prox;
    }
}
void swap_Lista(Lista *L1, Lista *L2)
{
    assert(L1 != NULL && L2 != NULL);
    assert(L1->size == L2->size);

    NoSent *aux;
    int len2 = L2->qtde;
    while (!empyt_Lista(L1))
    {
        aux = pop_front_no_Lista(L1);
        push_back_Lista(L2, aux->dado);
        delete_NoSent(&aux);
    }
    while (len2--)
    {
        aux = pop_front_no_Lista(L2);
        push_back_Lista(L1, aux->dado);
        delete_NoSent(&aux);
    }
}
void print_Lista(Lista *L, void (*print)(const void *))
{
    assert(L != NULL);

    printf("[ ");
    NoSent *aux = L->Sentinela->prox;
    while (aux->prox != L->Sentinela)
    {
        print(aux->dado);
        printf(", ");
        aux = aux->prox;
    }
    print(aux->dado);
    printf(" ]");
}
bool empyt_Lista(Lista *L)
{
    assert(L != NULL);
    return L->qtde == 0;
}
bool is_sorted_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    assert(L != NULL);

    // A iteração é feita no sentido convencional ( Direita -> Esquerda )
    NoSent *aux = L->Sentinela->prox;
    while (aux->prox != L->Sentinela)
    {
        if (GREATER_THAN(cmp(aux->dado, aux->prox->dado)))
            return false;
        aux = aux->prox;
    }
    return true;
}
bool is_reversed_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    assert(L != NULL);

    // A iteração é feita no sentido reverso ( Esquerda -> Direita  )
    NoSent *aux = L->Sentinela->ant;
    while (aux->ant != L->Sentinela)
    {
        if (GREATER_THAN(cmp(aux->dado, aux->ant->dado)))
            return false;
        aux = aux->ant;
    }
    return true;
}
void unique_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    assert(L != NULL);

    sort_Lista(L, cmp);
    NoSent *aux = L->Sentinela->prox; // Primeiro elemento da lista
    while (aux->prox != L->Sentinela && aux != L->Sentinela)
    {
        while (aux->prox != L->Sentinela && EQUAL_TO(cmp(aux->dado, aux->prox->dado)))
        {
            pop_in_Lista(L, aux->prox);
        }
        aux = aux->prox;
    }
}
void reverse_Lista(Lista *L)
{
    assert(L != NULL);

    NoSent *esq = L->Sentinela->prox;
    NoSent *dir = L->Sentinela->ant;
    if (IS_ODD(L->qtde))
    {
        while (esq != dir)
        {
            swap_NoSent(esq, dir);
            esq = esq->prox;
            dir = dir->ant;
        }
    }
    else
    {
        while (esq->ant != dir)
        {
            swap_NoSent(esq, dir);
            esq = esq->prox;
            dir = dir->ant;
        }
    }
}
void *Lista_to_array(Lista *L)
{
    void *r = calloc(L->qtde, L->size);
    NoSent *aux = L->Sentinela->prox;
    void *inc = r;
    for (int i = 0; i < L->qtde && aux != L->Sentinela; i++, inc += L->size)
    {
        memcpy(inc, aux->dado, L->size);
        //inc = aux->dado;
        aux = aux->prox;
    }
    return r;
}

NoSent *begin_Lista(Lista *L)
{
    return L->Sentinela->prox;
}
NoSent *end_Lista(Lista *L)
{
    return L->Sentinela;
}
void next_iter_Lista(NoSent **no)
{
    *no = (*no)->prox;
}

/* FUNCOES DE ORDENACAO */
void qsort_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    // Gasta o dobro de memória q o sort_Lista, porém é muito mais rapido
    // Para tamanho de lista menores que 1e6, nao vale muito a pena
    void *ar = Lista_to_array(L);
    qsort(ar, L->qtde, L->size, cmp);
    NoSent *aux = L->Sentinela->prox;
    void *inc = ar;
    for (int i = 0; i < L->qtde; i++, inc += L->size)
    {
        memcpy(aux->dado, inc, L->size);
        //aux->dado = inc;
        aux = aux->prox;
    }
    free(ar);
}
void sort_Lista(Lista *L, int (*cmp)(const void *, const void *))
{
    // Ordenação nao estavel dos elementos da lista
    // * É possível fazer uma ordenação estável se a função de comparação contiver os critérios de desempates implementados
    assert(L != NULL);

    // Fazer esta verificação impede um dos piores caso do quick_sort (quadratico)
    if (!is_sorted_Lista(L, cmp))
        _quick_sort_Lista(L, L->Sentinela->prox, L->Sentinela->ant, cmp);
}
static void _quick_sort_Lista(Lista *L, NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *))
{
    /*
     * A função abaixo é a versão em python que baseou esta versão.
     * 
     * def quick_sort_(vet, i, f):
     *     if i < f:
     *         p = partition(vet, i, f)
     *         quick_sort_(vet, i, p-1)
     *         quick_sort_(vet, p+1, f)
    */
    if (inicio != fim)
    {
        NoSent *p = _partition_Lista(inicio, fim, cmp);
        if (p != inicio)
            _quick_sort_Lista(L, inicio, p->ant, cmp); // quick_sort para esquerda
        if (p != fim)
            _quick_sort_Lista(L, p->prox, fim, cmp); // quick_sort para direita
    }
}
static NoSent *_partition_Lista(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *))
{
    /*
     * A função abaixo é a versão em python que baseou esta versão.
     * 
     * def partition(vet, inicio, fim):
     *     pivo = vet[fim]
     *     i = inicio-1
     *     for j in range(inicio, fim):
     *         if vet[j] < pivo:
     *             i += 1
     *             vet[j], vet[i] = vet[i], vet[j]
     *     vet[fim], vet[i+1] = vet[i+1], vet[fim]
     *     return i + 1
    */
    // As tres proximas linhas tentam melhorar um pouquinho a eficiencia do algoritmo
    // mas, se mostram irrelevantes
    GREATER_THAN(cmp(fim->ant->dado, fim)) ? swap_NoSent(fim, fim->ant) : 0;
    while (LESS_THAN(cmp(inicio->dado, fim->dado)))
        inicio = inicio->prox;

    NoSent *i = inicio->ant; // i: representa o ultimo menor elemnto encontrado
    while (inicio != fim)
    {
        if (LESS_THAN(cmp(inicio->dado, fim->dado)))
        {
            i = i->prox;
            swap_NoSent(inicio, i);
        }
        inicio = inicio->prox;
    }
    swap_NoSent(fim, i->prox);
    return i->prox;
}

#endif