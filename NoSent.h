typedef struct NoSent {
    void* dado ;
    size_t size;
    struct NoSent* prox ;
    struct NoSent* ant ;
} NoSent ;

/* FUNCOES DO NO */
NoSent* new_NoSent (void* elem, size_t s); // OK 18/06/2018
void copy_NoSent (const NoSent* dest, const NoSent* fonte); // OK 18/07/2018 """" NEED TO TEST """"
void swap_NoSent (NoSent* a, NoSent* b); // TODO
void delete_NoSent (NoSent** N); // OK 18/06/2018

/* IMPLEMENTACAO NO */

NoSent* new_NoSent (void* elem, size_t s){
    NoSent* novo = (NoSent*)calloc(1,sizeof(NoSent));

    novo->prox = novo->ant = NULL ;

    novo->dado = calloc(1, s);
    memcpy(novo->dado, elem, s);

    novo->size = s;

    return novo;
}
void copy_NoSent (const NoSent* dest, const NoSent* fonte){
    memcpy(dest->dado, fonte->dado, dest->size);
}
void swap_NoSent (NoSent* a, NoSent* b){
    void* tmp = a->dado;
    a->dado = b->dado;
    b->dado = tmp;
}
void delete_NoSent (NoSent** N){
    free((*N)->dado);
    free(*N);
}
