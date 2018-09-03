/*

lists são estruturas de dados que não é boa com buscas.
Se precisas fazer muitas buscas, utilize outra estrutura de dados.

*/
#ifndef LIST
#define LIST

#include "NoSent.h"

typedef struct
{
    NoSent *Sentinela;
    int qtde;
    size_t size;
} list;

/* CONSTRUTOR E DESTRUTOR */
list *new_list(size_t size);                                     // OK 18/06/2018
list *array_to_list(void *array, int length_array, size_t size); // OK 17/07/2018
void delete_list(list **self);                                   // OK 18/07/2018

/* FUNCOES DE BUSCA */
void *index_list(list *self, int pos);      // OK 24/06/2018
NoSent *index_no_list(list *self, int pos); // OK 18/06/2018

bool contains_list(list *self, void *elem, int (*cmp)(const void *, const void *));     // OK 24/06/2018
NoSent *search_no_list(list *self, void *elem, int (*cmp)(const void *, const void *)); // OK 24/06/2018

void *max_list(list *self, int (*cmp)(const void *, const void *));      // OK 18/07/2018
void *min_list(list *self, int (*cmp)(const void *, const void *));      // OK 18/07/2018
NoSent *max_no_list(list *self, int (*cmp)(const void *, const void *)); // OK 18/07/2018
NoSent *min_no_list(list *self, int (*cmp)(const void *, const void *)); // OK 18/07/2018

/* FUNCOES DE INSERCAO */
NoSent *push_no_list(list *self, void *elem, NoSent *pos); // OK 18/06/2018
bool push_back_list(list *self, void *elem);               // OK 18/06/2018
bool push_front_list(list *self, void *elem);              // OK 18/06/2018

bool insert_list(list *self, void *elem, int pos); // OK 18/06/2018

bool update_list(list *dest, const list *font);

/* FUNCOES DE REMOCAO */
NoSent *pop_in_list(list *self, NoSent *pos); // OK 18/06/2018
NoSent *pop_back_no_list(list *self);         // OK 24/06/2018
NoSent *pop_front_no_list(list *self);        // OK 24/06/2018
bool pop_back_list(list *self);               // OK 24/06/2018
bool pop_front_list(list *self);              // OK 24/06/2018
void *pop_back_dado_list(list *self);         // OK 24/06/2018
void *pop_front_dado_list(list *self);        // OK 24/06/2018

bool remove_list(list *self, void *elem, int (*cmp)(const void *, const void *)); // OK 24/06/2018
bool pop_list(list *self, int pos);                                               // OK 18/06/2018
void remove_if_list(list *self, bool (*condicao)(void *));                        // OK 18/06/2018

void clear_list(list *self); // OK 18/06/2018

/* FUNCOES AUXILIARES */
void copy_list(list *dest, const list *fonte);                             // OK 18/06/2018
void swap_list(list *L1, list *L2);                                        // OK 18/07/2018
void print_list(list *self, void (*print)(const void *));                  // OK 18/06/2018
bool empyt_list(list *self);                                               // OK 18/07/2018
void unique_list(list *self, int (*cmp)(const void *, const void *));      // OK 17/07/2018
bool is_sorted_list(list *self, int (*cmp)(const void *, const void *));   // OK 22/07/2018
bool is_reversed_list(list *self, int (*cmp)(const void *, const void *)); // OK 22/07/2018
void reverse_list(list *self);                                             // OK 17/07/2018
void *list_to_array(list *self);                                           // OK 17/07/2018
bool equals_list(const list *a, const list *b);                            // TODO

double sum_list(list *self, double (*cast)(const void *));  // TODO
double mult_list(list *self, double (*cast)(const void *)); // TODO

/* ITERADORES */
NoSent *begin_list(const list *self);  // OK 17/07/2018
NoSent *last_list(const list *self);   // OK 29/08/2018
NoSent *end_list(const list *self);    // OK 17/07/2018
void next_iter_list(NoSent **no);      // OK 17/07/2018
NoSent *rbegin_list(const list *self); // OK 29/08/2018
NoSent *rlast_list(const list *self);  // OK 29/08/2018
NoSent *rend_list(const list *self);   // OK 29/08/2018
void next_riter_list(NoSent **no);     // OK 29/08/2018

/* FUNCOES DE ORDENACAO */
void sort_list(list *self, int (*cmp)(const void *, const void *));                                            // OK 17/07/2018
static void _quick_sort_list(list *self, NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *)); // OK 17/07/2018
static NoSent *_partition_list(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *));           // OK 17/07/2018
static NoSent *_partition_list2(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *));

/* IMPLEMENTACOES LISTA */

/* CONSTRUTOR E DESTRUTOR */
list *new_list(size_t size)
{
    if (SizeError(size, "new_list"))
        return NULL;

    list *self = (list *)malloc(sizeof(list));
    self->Sentinela = create_Sent();
    self->qtde = 0;
    self->size = size;
    return self;
}
list *array_to_list(void *array, int length_array, size_t size)
{
    if (array == NULL)
    {
        printf("\nError. The array variable must not be null.\n");
        return NULL;
    }
    if (length_array <= 0)
    {
        printf("\nError. Variable length_array must be greater than zero (0).\n");
        return NULL;
    }
    if (SizeError(size, "array_to_list"))
        return NULL;

    list *self = new_list(size);
    void *it = array;
    for (int i = 0; i < length_array; i++, it += size)
        push_back_list(self, it);
    return self;
}

list *new_random_int_list(int begin, int end, int array_length)
{
    if (begin > end)
        swap(&begin, &end, sizeof(int));

    list *self = new_list(sizeof(int));

    int range = end - begin;
    int *a;
    srand((unsigned)time(NULL));
    for (int i = 0; i < array_length; i++)
    {
        a = (int *)malloc(sizeof(int));
        *a = (rand() % range) + begin;
        push_back_list(self, a);
    }

    return self;
}

void delete_list(list **self)
{
    if (NullPointerError(*self, "delete_list"))
        return;

    clear_list(*self);
    delete_NoSent(&((*self)->Sentinela));
    free(*self);
    *self = NULL;
}

/* FUNCOES DE BUSCA */
NoSent *index_no_list(list *self, int pos)
{
    if (NullPointerError(self, "index_no_list"))
        return NULL;
    if (IndexOutOfTheRangeError(pos, -self->qtde, self->qtde + 1, "index_no_list"))
        return NULL;
    if (empyt_list(self))
        return NULL;

    if (pos < 0)
        pos += self->qtde + 1;

    NoSent *aux;
    if (pos > self->qtde / 2)
    {
        aux = rbegin_list(self);
        for (int i = self->qtde; i > pos; i--)
            next_riter_list(&aux);
    }
    else
    {
        aux = begin_list(self);
        for (int i = 1; i < pos; i++)
            next_iter_list(&aux);
    }
    return aux;
}
void *index_list(list *self, int pos)
{
    NoSent *aux = index_list(self, pos);
    return aux != NULL ? aux->dado : NULL;
}

NoSent *search_no_list(list *self, void *elem, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "search_no_list"))
        return NULL;

    NoSent *aux = begin_list(self);
    while (aux != end_list(self))
    {
        if (EQUAL_TO(cmp(elem, aux->dado)))
            return aux;
        next_iter_list(&aux);
    }
    return NULL;
}
bool contains_list(list *self, void *elem, int (*cmp)(const void *, const void *))
{
    return search_no_list(self, elem, cmp) != NULL;
}

NoSent *max_no_list(list *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "max_no_list"))
        return NULL;
    if (empyt_list(self))
        return NULL;

    NoSent *aux = begin_list(self);
    NoSent *max = aux;
    while (aux != end_list(self))
    {
        if (GREATER_THAN(cmp(aux->dado, max->dado)))
            max = aux;
        next_iter_list(&aux);
    }
    return max;
}
void *max_list(list *self, int (*cmp)(const void *, const void *))
{
    NoSent *aux = max_no_list(self, cmp);
    if (aux != NULL)
    {
        return aux->dado;
    }
    return NULL;
}

NoSent *min_no_list(list *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "min_no_list"))
        return NULL;
    if (empyt_list(self))
        return NULL;

    NoSent *aux = begin_list(self);
    NoSent *min = aux;
    while (aux != end_list(self))
    {
        if (LESS_THAN(cmp(min->dado, aux->dado)))
            min = aux;
        next_iter_list(&aux);
    }
    return min;
}
void *min_list(list *self, int (*cmp)(const void *, const void *))
{
    NoSent *aux = min_no_list(self, cmp);
    return aux != NULL ? aux->dado : NULL;
}

/* FUNCOES DE INSERCAO */
NoSent *push_no_list(list *self, void *elem, NoSent *pos)
{
    // Coloca o elemento 'elem' apos o no 'pos' na lista 'self'
    if (NullPointerError(self, "push_no_list"))
        return NULL;
    if (NullPointerError(elem, "push_no_list"))
        return NULL;

    if (pos == NULL)
        return NULL;

    NoSent *novo = new_NoSent(elem, self->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    self->qtde++;

    return novo;
}
bool push_back_list(list *self, void *elem)
{
    return push_no_list(self, elem, last_list(self)) != NULL;
}
bool push_front_list(list *self, void *elem)
{
    return push_no_list(self, elem, end_list(self)) != NULL;
}

bool insert_list(list *self, void *elem, int pos)
{
    NoSent *index = index_no_list(self, pos);
    return index != NULL ? push_no_list(self, elem, index) != NULL : false;
}

bool update_list(list *dest, const list *font)
{
    if (NullPointerError(dest, "push_no_list"))
        return false;
    if (NullPointerError(font, "push_no_list"))
        return false;
    if (dest->size != font->size)
    {
        printf("\nError. Size of the list must be equal.\n");
        return false;
    }

    NoSent *aux = begin_list(font);
    while (aux != font->Sentinela)
    {
        push_back_list(dest, aux->dado);
        next_iter_list(&aux);
    }
}

/* FUNCOES DE REMOCAO */
NoSent *pop_in_list(list *self, NoSent *pos)
{
    if (NullPointerError(self, "pop_in_list"))
        return NULL;
    if (NullPointerError(pos, "pop_in_list"))
        return NULL;
    if (pos == end_list(self))
        return NULL;

    // Desenlaçando os nós
    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    // Removendo as referências
    pos->prox = pos->ant = NULL;

    self->qtde--;

    return pos;
}

NoSent *pop_back_no_list(list *self)
{
    return pop_in_list(self, last_list(self));
}
bool pop_back_list(list *self)
{
    NoSent *aux = pop_back_no_list(self);
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void *pop_back_dado_list(list *self)
{
    NoSent *aux = pop_back_no_list(self);
    void *dado = NULL;
    if (aux != NULL)
    {
        dado = memcpy(malloc(aux->size), aux->dado, aux->size);
        delete_NoSent(&aux);
    }
    return dado;
}

NoSent *pop_front_no_list(list *self)
{
    return pop_in_list(self, begin_list(self));
}
bool pop_front_list(list *self)
{
    NoSent *aux = pop_front_no_list(self);
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void *pop_front_dado_list(list *self)
{
    NoSent *aux = pop_front_no_list(self);
    void *dado = NULL;
    if (aux != NULL)
    {
        dado = memcpy(malloc(aux->size), aux->dado, aux->size);
        delete_NoSent(&aux);
    }
    return dado;
}
bool remove_list(list *self, void *elem, int (*cmp)(const void *, const void *))
{
    NoSent *aux = pop_in_list(self, search_no_list(self, elem, cmp));
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
bool pop_list(list *self, int pos)
{
    NoSent *aux = pop_in_list(self, index_no_list(self, pos));
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void remove_if_list(list *self, bool (*condicao)(void *))
{
    if (NullPointerError(self, "remove_if_list"))
        return;

    NoSent *aux = begin_list(self);
    while (aux != end_list(self))
    {
        if (condicao(aux->dado))
        {
            next_iter_list(&aux);
            NoSent *tmp = pop_in_list(self, aux->ant);
            delete_NoSent(&tmp);
        }
        else
            next_iter_list(&aux);
    }
}

void clear_list(list *self)
{
    if (NullPointerError(self, "clear_list"))
        return;
    NoSent *aux = pop_back_no_list(self);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_front_no_list(self);
    }
}

/* FUNCOES AUXILIARES */
void copy_list(list *dest, const list *font)
{
    if (NullPointerError(dest, "copy_list"))
        return;
    if (NullPointerError(font, "copy_list"))
        return;

    if (dest->size != font->size)
    {
        printf("\nError. Size of the list must be equal.\n");
        return;
    }

    clear_list(dest);

    NoSent *aux = begin_list(font);
    while (aux != font->Sentinela)
    {
        push_back_list(dest, aux->dado);
        next_iter_list(&aux);
    }
}
void swap_list(list *L1, list *L2)
{
    if (NullPointerError(L1, "swap_list"))
        return;
    if (NullPointerError(L2, "swap_list"))
        return;

    NoSent *aux;
    int len2 = L2->qtde;
    while (!empyt_list(L1))
    {
        aux = pop_front_no_list(L1);
        push_back_list(L2, aux->dado);
        delete_NoSent(&aux);
    }
    while (len2--)
    {
        aux = pop_front_no_list(L2);
        push_back_list(L1, aux->dado);
        delete_NoSent(&aux);
    }
}
void print_list(list *self, void (*print)(const void *))
{
    if (NullPointerError(self, "print_list"))
        return;

    NoSent *aux = begin_list(self);
    printf("[");
    while (aux->prox != end_list(self))
    {
        printf(" ");
        print(aux->dado);
        printf(",");
        next_iter_list(&aux);
    }
    if (aux != end_list(self))
    {
        printf(" ");
        print(aux->dado);
        printf(" ");
    }
    printf("]");
}
bool empyt_list(list *self)
{
    if (NullPointerError(self, "empyt_list"))
        return true;
    return self->qtde == 0;
}
bool is_sorted_list(list *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "is_sorted_list"))
        return false;

    // A iteração é feita no sentido convencional ( Direita -> Esquerda )
    NoSent *aux = begin_list(self);
    while (aux->prox != end_list(self))
    {
        if (GREATER_THAN(cmp(aux->dado, aux->prox->dado)))
            return false;
        next_iter_list(&aux);
    }
    return true;
}
bool is_reversed_list(list *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "is_reversed_list"))
        return false;

    // A iteração é feita no sentido reverso ( Esquerda -> Direita  )
    NoSent *aux = last_list(self);
    while (aux->ant != end_list(self))
    {
        if (GREATER_THAN(cmp(aux->dado, aux->ant->dado)))
            return false;
        aux = aux->ant;
    }
    return true;
}
void unique_list(list *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "unique_list"))
        return;

    sort_list(self, cmp);
    NoSent *aux = begin_list(self); // Primeiro elemento da lista
    while (aux->prox != end_list(self) && aux != end_list(self))
    {
        while (aux->prox != end_list(self) && EQUAL_TO(cmp(aux->dado, aux->prox->dado)))
        {
            pop_in_list(self, aux->prox);
        }
        next_iter_list(&aux);
    }
}
void reverse_list(list *self)
{
    if (NullPointerError(self, "reverse_list"))
        return;

    NoSent *esq = begin_list(self);
    NoSent *dir = last_list(self);
    if (IS_ODD(self->qtde))
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
void *list_to_array(list *self)
{
    if (NullPointerError(self, "list_to_array"))
        return NULL;
    void *r = calloc(self->qtde, self->size);
    NoSent *aux = begin_list(self);
    void *inc = r;
    for (int i = 0; i < self->qtde && aux != end_list(self); i++, inc += self->size)
    {
        memcpy(inc, aux->dado, self->size);
        next_iter_list(&aux);
    }
    return r;
}

/* ITERADORES */
NoSent *rbegin_list(const list *self)
{
    return last_list(self);
}
NoSent *rend_list(const list *self)
{
    return end_list(self);
}
NoSent *rlast_list(const list *self)
{
    return begin_list(self);
}
void next_riter_list(NoSent **no)
{
    *no = (*no)->ant;
}
NoSent *begin_list(const list *self)
{
    return self->Sentinela->prox;
}
NoSent *last_list(const list *self)
{
    return self->Sentinela->ant;
}
NoSent *end_list(const list *self)
{
    return self->Sentinela;
}
void next_iter_list(NoSent **no)
{
    *no = (*no)->prox;
}

/* FUNCOES DE ORDENACAO */
void qsort_list(list *self, int (*cmp)(const void *, const void *))
{
    // Gasta o dobro de memória q o sort_list, porém é muito mais rapido
    // Para tamanho de lista menores que 1e6, nao vale muito a pena
    if (NullPointerError(self, "qsort_list"))
        return;
    void *ar = list_to_array(self);
    qsort(ar, self->qtde, self->size, cmp);
    NoSent *aux = begin_list(self);
    void *inc = ar;
    for (int i = 0; i < self->qtde; i++, inc += self->size)
    {
        memcpy(aux->dado, inc, self->size);
        next_iter_list(&aux);
    }
    free(ar);
}
void sort_list(list *self, int (*cmp)(const void *, const void *))
{
    // Ordenação nao estavel dos elementos da lista
    // * É possível fazer uma ordenação estável se a função de comparação contiver os critérios de desempates implementados
    if (NullPointerError(self, "sort_list"))
        return;
    // Fazer esta verificação impede um dos piores caso do quick_sort (quadratico)
    if (!is_sorted_list(self, cmp))
        _quick_sort_list(self, begin_list(self), last_list(self), cmp);
}

static void _quick_sort_list(list *self, NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *))
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
    static int count = 0;
    static int deep = 0;
    printf("%d,%d,%d,%d,%d\n", count, deep, inicio, fim, fim - inicio);
    deep++;
    count++;
    if (inicio != fim)
    {
        NoSent *p = _partition_list(inicio, fim, cmp);

        if (p != inicio)
            _quick_sort_list(self, inicio, p->ant, cmp); // quick_sort para esquerda
        if (p != fim)
            _quick_sort_list(self, p->prox, fim, cmp); // quick_sort para direita

        deep--;
    }
}
static NoSent *_partition_list(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *))
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

    LESS_THAN(cmp(fim->ant->dado, fim)) ? swap_NoSent(fim, fim->ant) : 0;
    while (LESS_THAN(cmp(inicio->dado, fim->dado)))
        inicio = inicio->prox;

    NoSent *i = inicio->ant; // i: representa o ultimo menor elemento encontrado
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