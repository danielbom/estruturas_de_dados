
typedef struct No_lista {
    void* dado ;
    size_t size;
    struct No_lista *prox ;
    struct No_lista *ant ;
} No_lista ;

typedef struct {
    No_lista *Sentinela ;
    int tam ;
    size_t size ;
} Lista ;

/* CONSTRUTOR E DESTRUTOR */
Lista* new_Lista (size_t size) ;  // OK
void delete_Lista (Lista *L) ;    // OK

/* FUNCOES DE BUSCA */
No_lista* index_Lista(Lista* L, int pos); // OK
No_lista* search_Lista(Lista* L, void* elem, int(*Comparar)(void*,void*));   // OK

/* FUNCOES DE INSERCAO */
No_lista* push_ant_Lista (Lista *L, void* elem, No_lista* pos) ; // OK
No_lista* push_back_Lista (Lista *L, void* elem) ;        // OK
No_lista* push_front_Lista (Lista *L, void* elem) ;       // OK

No_lista* insert_Lista(Lista* L, void* elem, int pos);    // OK

/* FUNC��ES DE REMO��O */
No_lista* pop_back_Lista (Lista *L) ;         // OK
No_lista* pop_front_Lista (Lista *L) ;        // OK
No_lista* pop_in_Lista(Lista* L, No_lista* pos) ;   // OK

No_lista* remove_Lista(Lista* L, void* elem, int(*Comparar)(void*,void*)); // OK
No_lista* pop_Lista (Lista* L, int pos);      // OK

void clear_Lista (Lista* L);

/* FUNCOES AUXILIARES */
void copy_Lista (Lista *dest, const Lista* fonte);
void swap_Lista (Lista* L1, Lista *L2);
void print_Lista (Lista *L, void(*print)(void*)) ;

/* FUNCOES DO NO */
No_lista* new_No_lista(void* elem, size_t s) ; // OK
void copy_No_lista(No_lista *dest, const No_lista* fonte); // OK
void delete_No_lista(No_lista* N); // OK

No_lista* new_No_lista(void* elem, size_t s){
    No_lista* novo = (No_lista*)calloc(1,sizeof(No_lista));

    novo->prox = novo->ant = NULL ;

    novo->dado = calloc(1, s);
    memcpy(novo->dado, elem, s);

    novo->size = s;

    return novo;
}
void copy_No_lista(No_lista *dest, const No_lista* fonte){
    dest = new_No_lista(fonte->dado, fonte->size);
}
void delete_No_lista(No_lista* N){
    free(N->dado);
    free(N);
}

/* IMPLEMENTA��ES LISTA */
Lista* new_Lista(size_t size){
    Lista* L = (Lista*) malloc (sizeof(Lista));

    void* aux = calloc(1,size);
    L->Sentinela = new_No_lista(calloc(1,size), size);
    free(aux);

    L->Sentinela->ant = L->Sentinela->prox = L->Sentinela;

    L->tam = 0;
    L->size = size;

    return L;
}
void delete_Lista(Lista* L){
    clear_Lista(L);
    delete_No_lista(L->Sentinela);
    free(L);
}

No_lista* index_Lista(Lista* L, int pos){
    if(pos > L->tam) return NULL;
    No_lista* aux ;
    int i;
    if(pos > L->tam/2){
        aux = L->Sentinela->ant;
        for(i=L->tam; i>pos; i--){
            aux = aux->ant;
        }
    }
    else{
        aux = L->Sentinela->prox;
        for(i=1; i<pos; i++){
            aux = aux->prox;
        }
    }
    return aux;
}
No_lista* search_Lista(Lista* L, void* elem, int(*Comparar)(void*,void*)){
    No_lista* aux = L->Sentinela->prox;
    while(aux != L->Sentinela){
        if(Comparar(elem, aux->dado) == 0){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

No_lista* push_ant_Lista (Lista *L, void* elem, No_lista* pos){
    if(pos == NULL) return NULL;
    if(elem == NULL) return NULL;
    if(L == NULL) return NULL;

    No_lista* novo = new_No_lista(elem, L->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    L->tam++;

    return novo;
}
No_lista* push_back_Lista (Lista *L, void* elem){
    return push_ant_Lista(L, elem, L->Sentinela->ant);
}
No_lista* push_front_Lista (Lista *L, void* elem){
    return push_ant_Lista(L, elem, L->Sentinela);
}

No_lista* insert_Lista(Lista* L, void* elem, int pos){
    return push_ant_Lista(L, elem, index_Lista(L, pos));
}

No_lista* pop_in_Lista(Lista* L, No_lista* pos){
    if(L == NULL) return NULL;
    if(pos == NULL) return NULL;
    if(pos == L->Sentinela) return NULL;

    pos->ant->prox = pos->prox ;
    pos->prox->ant = pos->ant ;

    pos->prox = pos->ant = NULL;

    L->tam--;

    return pos;
}
No_lista* pop_back_Lista(Lista* L){
    return pop_in_Lista(L, L->Sentinela->ant);
}
No_lista* pop_front_Lista (Lista *L){
    return pop_in_Lista(L, L->Sentinela->prox);
}

No_lista* remove_Lista(Lista* L, void* elem, int(*Comparar)(void*,void*)){
    return pop_in_Lista(L, search_Lista(L, elem, Comparar));
}
No_lista* pop_Lista (Lista* L, int pos){
    return pop_in_Lista(L, index_Lista(L, pos));
}

void clear_Lista (Lista* L){
    No_lista* aux = pop_back_Lista(L);
    while(aux != NULL){
        delete_No_lista(aux);
        aux = pop_back_Lista(L);
    }
}
void copy_Lista (Lista *dest, const Lista* fonte){
    if(dest == NULL) return ;
    if(dest->size != fonte->size) return ;
    if(dest->tam != 0) {
        clear_Lista(dest);
    }
    No_lista* aux = fonte->Sentinela->prox;
    while(aux != fonte->Sentinela){
        push_back_Lista(dest, aux->dado);
        aux = aux->prox;
    }
}
void swap_Lista (Lista* L1, Lista *L2){
    if(L1 == NULL || L2 == NULL) return ;
    if(L1->size != L2->size) return;
    Lista* L = new_Lista(L1->size);
    copy_Lista(L, L1);
    copy_Lista(L1, L2);
    copy_Lista(L2, L);
    delete_Lista(L);
}

void print_Lista(Lista *L, void(*print)(void*)){
    No_lista* aux = L->Sentinela->prox;
    while(aux!=L->Sentinela){
        (*print)(aux->dado);
        aux = aux->prox;
    }
}


