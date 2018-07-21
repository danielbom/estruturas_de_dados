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
#include "NoSent.h"

typedef struct {
    NoSent* Sentinela ;
    int qtde ;
    size_t size ;
} Lista ;

/* CONSTRUTOR E DESTRUTOR */
Lista* new_Lista (size_t size) ; // OK 18/06/2018
Lista* array_to_Lista(void* array, int length_array, size_t size); // OK 17/07/2018
void delete_Lista (Lista** L) ; // OK 18/07/2018

/* FUNCOES DE BUSCA */
NoSent* index_Lista (Lista* L, int pos); // OK 18/06/2018
NoSent* search_Lista (Lista* L, void* elem, int(*cmp)(const void*,const void*)); // OK 18/06/2018
NoSent* max_Lista(Lista* L, int(*cmp)(const void*, const void*)); // OK 18/07/2018
NoSent* min_Lista(Lista* L, int(*cmp)(const void*, const void*)); // OK 18/07/2018

/* FUNCOES DE INSERCAO */
NoSent* push_ant_Lista (Lista* L, void* elem, NoSent* pos) ; // OK 18/06/2018
NoSent* push_back_Lista (Lista* L, void* elem) ; // OK 18/06/2018
NoSent* push_front_Lista (Lista* L, void* elem) ; // OK 18/06/2018

NoSent* insert_Lista (Lista* L, void* elem, int pos); // OK 18/06/2018

/* FUNCOES DE REMOCAO */
NoSent* pop_back_Lista (Lista* L) ; // OK 18/06/2018
NoSent* pop_front_Lista (Lista* L) ; // OK 18/06/2018
NoSent* pop_in_Lista (Lista* L, NoSent* pos) ; // OK 18/06/2018

NoSent* remove_Lista (Lista* L, void* elem, int(*cmp)(const void*,const void*)); // OK 18/06/2018
NoSent* pop_Lista (Lista* L, int pos); // OK 18/06/2018
void remove_if_Lista (Lista* L, bool(*condicao)(void*)); // OK 18/06/2018

void clear_Lista (Lista* L); // OK 18/06/2018

/* FUNCOES AUXILIARES */
void copy_Lista (Lista* dest, const Lista* fonte); // OK 18/06/2018
void swap_Lista (Lista* L1, Lista* L2); // OK 18/07/2018
void print_Lista (Lista* L, void(*print)(const void*)) ; // OK 18/06/2018
bool empyt_Lista (Lista* L); // OK 18/07/2018
void unique_Lista (Lista* L, int(*cmp)(const void*,const void*)) ; // OK 17/07/2018
bool is_sorted_Lista (Lista* L, int(*cmp)(const void*,const void*), bool reversed); // OK 17/07/2018
void reverse_Lista (Lista* L);
void* Lista_to_array(Lista* L);

NoSent* begin_Lista(Lista* L);
NoSent* end_Lista(Lista* L);
void next_iter_Lista(NoSent** no);

/* FUNCOES DE ORDENACAO */
void sort_Lista (Lista* L, int(*cmp)(const void*,const void*)); // OK 17/07/2018
static void _quick_sort_Lista (NoSent* inicio, NoSent* fim, int(*cmp)(const void*,const void*)); // OK 17/07/2018
static NoSent* _partition_Lista (NoSent* inicio, NoSent* fim, int(*cmp)(const void*,const void*)); // OK 17/07/2018

/* IMPLEMENTACOES LISTA */

/* CONSTRUTOR E DESTRUTOR */
Lista* new_Lista (size_t size){
    assert(size > 0);

    Lista* L = (Lista*) malloc (sizeof(Lista));

    void* aux = calloc(1,size);
    L->Sentinela = new_NoSent(calloc(1,size), size);
    free(aux);

    L->Sentinela->ant = L->Sentinela->prox = L->Sentinela;

    L->qtde = 0;
    L->size = size;

    return L;
}
Lista* array_to_Lista (void* array, int length_array, size_t size){
    assert(array != NULL);
    assert(length_array > 0);
    assert(size > 0);

    Lista* L = new_Lista(size);
    void* it = array;
    for(int i = 0; i < length_array; i++){
        push_back_Lista(L, array + i*size);
    }
    return L;
}
void delete_Lista (Lista** L){
    assert(*L != NULL);

    clear_Lista(*L);
    delete_NoSent(&((*L)->Sentinela));
    free(*L);
    *L = NULL;
}

/* FUNCOES DE BUSCA */
NoSent* index_Lista (Lista* L, int pos){
    assert(L != NULL);

    if(pos > L->qtde) return NULL;
    if(L->qtde == 0) return NULL;
    if(pos < 0) pos += L->qtde + 1;

    NoSent* aux ;
    int i;
    if(pos > L->qtde/2){
        aux = L->Sentinela->ant;
        for(i=L->qtde; i>pos; i--) aux = aux->ant;
    }
    else{
        aux = L->Sentinela->prox;
        for(i=1; i<pos; i++) aux = aux->prox;
    }
    return aux;
}
NoSent* search_Lista (Lista* L, void* elem, int(*cmp)(const void*,const void*)){
    assert(L != NULL);

    NoSent* aux = L->Sentinela->prox;
    while(aux != L->Sentinela){
        if(cmp(elem, aux->dado) == 0) return aux;
        aux = aux->prox;
    }
    return NULL;
}
NoSent* max_Lista(Lista* L, int(*cmp)(const void*, const void*)){
    assert(L != NULL);

    NoSent* aux = L->Sentinela->prox;
    NoSent* max = L->Sentinela->prox;
    while(aux != L->Sentinela){
        if(cmp(max->dado, aux->dado) < 0) max = aux;
        aux = aux->prox;
    }
    return max->dado;
}
NoSent* min_Lista(Lista* L, int(*cmp)(const void*, const void*)){
    assert(L != NULL);

    NoSent* aux = L->Sentinela->prox;
    NoSent* min = L->Sentinela->prox;
    while(aux != L->Sentinela){
        if(cmp(min->dado, aux->dado) > 0) min = aux;
        aux = aux->prox;
    }
    return min->dado;
}

/* FUNCOES DE INSERCAO */
NoSent* push_ant_Lista (Lista* L, void* elem, NoSent* pos){
    assert(L != NULL);

    if(pos == NULL) return NULL;

    NoSent* novo = new_NoSent(elem, L->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    L->qtde++;

    return novo;
}
NoSent* push_back_Lista (Lista* L, void* elem){
    return push_ant_Lista(L, elem, L->Sentinela->ant);
}
NoSent* push_front_Lista (Lista* L, void* elem){
    return push_ant_Lista(L, elem, L->Sentinela);
}

NoSent* insert_Lista (Lista* L, void* elem, int pos){
    return push_ant_Lista(L, elem, index_Lista(L, pos));
}

/* FUNCOES DE REMOCAO */
NoSent* pop_in_Lista (Lista* L, NoSent* pos){
    assert(L != NULL);

    if(pos == NULL) return NULL;
    if(pos == L->Sentinela) return NULL;

    pos->ant->prox = pos->prox ;
    pos->prox->ant = pos->ant ;

    pos->prox = pos->ant = NULL;

    L->qtde--;

    return pos;
}
NoSent* pop_back_Lista (Lista* L){
    return pop_in_Lista(L, L->Sentinela->ant);
}
NoSent* pop_front_Lista (Lista* L){
    return pop_in_Lista(L, L->Sentinela->prox);
}

NoSent* remove_Lista (Lista* L, void* elem, int(*cmp)(const void*,const void*)){
    return pop_in_Lista(L, search_Lista(L, elem, cmp));
}
NoSent* pop_Lista (Lista* L, int pos){
    return pop_in_Lista(L, index_Lista(L, pos));
}
void remove_if_Lista (Lista* L, bool(*condicao)(void*)){
    assert(L != NULL);

    NoSent* aux = L->Sentinela->prox;
    while (aux != L->Sentinela){
        if (condicao(aux->dado)){
            NoSent* tmp = aux->prox;
            aux = pop_in_Lista(L, aux);
            delete_NoSent(&aux);
            aux = tmp;
        }
        else {
            aux = aux->prox;
        }
    }
}

void clear_Lista (Lista* L){
    assert(L != NULL);

    NoSent* aux = pop_back_Lista(L);
    while(aux != NULL){
        delete_NoSent(&aux);
        aux = pop_back_Lista(L);
    }
}

/* FUNCOES AUXILIARES */
void copy_Lista (Lista* dest, const Lista* font){
    assert(dest != NULL && font != NULL);

    if(dest->size != font->size) return ;
    if(dest->qtde != 0) clear_Lista(dest);

    NoSent* aux = font->Sentinela->prox;
    while(aux != font->Sentinela){
        push_back_Lista(dest, aux->dado);
        aux = aux->prox;
    }
}
void swap_Lista (Lista* L1, Lista *L2){
    assert(L1 != NULL && L2 != NULL);
    assert(L1->size == L2->size);

    NoSent* aux;
    int len2 = L2->qtde;
    while(!empyt_Lista(L1)){
        aux = pop_front_Lista(L1);
        push_back_Lista(L2, aux->dado);
        delete_NoSent(&aux);
    }
    while(len2--){
        aux = pop_front_Lista(L2);
        push_back_Lista(L1, aux->dado);
        delete_NoSent(&aux);
    }
}
void print_Lista (Lista* L, void(*print)(const void*)){
    assert(L != NULL);

    NoSent* aux = L->Sentinela->prox;
    while(aux!=L->Sentinela){
        (*print)(aux->dado);
        aux = aux->prox;
    }
}
bool empyt_Lista (Lista* L){
    assert(L != NULL);
    return L->qtde == 0;
}
bool is_sorted_Lista (Lista* L, int(*cmp)(const void*,const void*), bool reversed){
    assert(L != NULL);

    if(!reversed){
        // A iteração é feita no sentido convencional ( Direita -> Esquerda )
        NoSent* aux = L->Sentinela->prox;
        while(aux->prox != L->Sentinela){
            if(cmp(aux->dado, aux->prox->dado) > 0) return false;
            aux = aux->prox;
        }
    }
    else{
        // A iteração é feita no sentido reverso ( Esquerda -> Direita  )
        NoSent* aux = L->Sentinela->ant;
        while(aux->ant != L->Sentinela){
            if(cmp(aux->dado, aux->ant->dado) > 0) return false;
            aux = aux->ant;
        }
    }
    return true;
}
void unique_Lista (Lista* L, int(*cmp)(const void*,const void*)){
    assert(L != NULL);

    sort_Lista(L, cmp);
    NoSent* aux = L->Sentinela->prox;
    while( aux->prox != L->Sentinela && aux != L->Sentinela){
        while( aux->prox != L->Sentinela && cmp(aux->dado, aux->prox->dado) == 0 ){
            pop_in_Lista(L, aux->prox);
        }
        aux = aux->prox;
    }
}
void reverse_Lista (Lista* L){
    assert(L != NULL);
    
    NoSent* esq = L->Sentinela->prox;
    NoSent* dir = L->Sentinela->ant;
    if(L->qtde % 2 == 1){
        while(esq != dir){
            swap_NoSent(esq, dir);
            esq = esq->prox;
            dir = dir->ant;
        }
    }
    else{
        while(esq->ant != dir){
            swap_NoSent(esq, dir);
            esq = esq->prox;
            dir = dir->ant;
        }
    }
}
void* Lista_to_array(Lista* L){
    void* r = calloc (L->qtde, L->size);
    NoSent* aux = L->Sentinela->prox;
    void* inc = r;
    for(int i=0; i<L->qtde; i++, inc += L->size){
        //memcpy(inc, aux->dado, L->size);
        inc = aux->dado;
        aux = aux->prox;
    }
    return r;
}

NoSent* begin_Lista(Lista* L){
    return L->Sentinela->prox;
}
NoSent* end_Lista(Lista* L){
    return L->Sentinela;
}
void next_iter_Lista(NoSent** no){
    *no = (*no)->prox;
}

/* FUNCOES DE ORDENACAO */
void sort_Lista (Lista* L, int(*cmp)(const void*, const void*)){
    assert(L != NULL);
    /* Ordenação nao estavel dos elementos da lista */
    /* Fazer esta verificação impede um dos piores caso do quick_sort (quadratico) */
    if(!is_sorted_Lista(L, cmp, false)) _quick_sort_Lista(L->Sentinela->prox, L->Sentinela->ant, cmp);
}
static void _quick_sort_Lista (NoSent* inicio, NoSent* fim, int(*cmp)(const void*,const void*)){
    /*
     * A função abaixo é a versão em python que baseou esta versão.
     * 
     * def quick_sort_(vet, i, f):
     *     if i < f:
     *         p = partition(vet, i, f)
     *         quick_sort_(vet, i, p-1)
     *         quick_sort_(vet, p+1, f)
    */
    if(inicio != fim){
        NoSent* p = _partition_Lista(inicio, fim, cmp);
        if(p != inicio) _quick_sort_Lista(inicio, p->ant, cmp);  // quick_sort to left
        if(p != fim) _quick_sort_Lista(p->prox, fim, cmp); // quick_sort to right
    }
}
static NoSent* _partition_Lista (NoSent* inicio, NoSent* fim, int(*cmp)(const void*,const void*)){
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
    NoSent* i = inicio->ant;
    while( inicio != fim ){
        if(cmp(inicio->dado, fim->dado) < 0){
            i = i->prox;
            swap_NoSent(inicio,i);
        }
        inicio = inicio->prox;
    }
    swap_NoSent(fim, i->prox);
    return i->prox;
}