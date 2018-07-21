typedef struct NoTree {
    void* dado ;
    size_t size;
    struct NoTree* dir ;
    struct NoTree* esq ;
} NoTree ;

/* FUNCOES DO NO */
NoTree* new_NoTree (void* elem, size_t s) ; // OK 18/06/2018
void copy_NoTree (NoTree* dest, const NoTree* fonte); // OK 18/06/2018
void swap_NoTree (NoTree* a, NoTree* b); // TODO
void delete_NoTree (NoTree** N); // OK 18/06/2018

/* IMPLEMENTACAO NO */
NoTree* new_NoTree (void* elem, size_t s){
    NoTree* novo = (NoTree*)calloc(1,sizeof(NoTree));

    novo->dir = novo->esq = NULL ;

    novo->dado = calloc(1, s);
    memcpy(novo->dado, elem, s);

    novo->size = s;

    return novo;
}
void copy_NoTree (NoTree* dest, const NoTree* fonte){
    dest = new_NoTree(fonte->dado, fonte->size);
}
void swap_NoTree (NoTree* a, NoTree* b){
    void* tmp = a->dado;
    a->dado = b->dado;
    b->dado = tmp;
}
void delete_NoTree (NoTree** N){
    free((*N)->dado);
    free(*N);
}
