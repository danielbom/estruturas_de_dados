typedef struct No_pilha {
    void* dado ;
    size_t size;
    struct No_pilha *prox ;
    struct No_pilha *ant ;
} No_pilha ;

typedef struct {
    No_pilha *Topo ;
    int tam ;
    size_t size ;
} Pilha ;

/* CONSTRUTOR E DESTRUTOR */
Pilha* new_Pilha (size_t size);     // OK
void delete_Pilha (Pilha *P);       // OK

/* FUNCOES DE INSERCAO */
No_pilha* push_Pilha (Pilha *P, void* elem);  // OK

/* FUNCOES DE REMOCAO */
No_pilha* pop_Pilha (Pilha *P);           // OK

void clear_Pilha (Pilha* P);        // OK

/* FUNCOES AUXILIARES */
void reverse_Pilha (Pilha* P);  // OK
void _reverse_Pilha(Pilha* P);  // OK
void copy_Pilha (Pilha *dest, const Pilha* fonte);  // OK
void swap_Pilha (Pilha* P1, Pilha *P2);             // OK
void print_Pilha (Pilha *P, void(*print)(void*)) ;  // OK

/* FUNCOES No_pilha */
No_pilha* new_No_pilha(void* elem, size_t s) ; // OK
void copy_No_pilha(No_pilha *dest, const No_pilha* fonte); // OK
void delete_No_pilha(No_pilha* N); // OK

No_pilha* new_No_pilha(void* elem, size_t s){
    No_pilha* No_pilhavo = (No_pilha*)calloc(1,sizeof(No_pilha));

    No_pilhavo->prox = NULL ;

    No_pilhavo->dado = calloc(1, s);
    memcpy(No_pilhavo->dado, elem, s);

    No_pilhavo->size = s;

    return No_pilhavo;
}
void copy_No_pilha(No_pilha *dest, const No_pilha* fonte){
    dest = new_No_pilha(fonte->dado, fonte->size);
}
void delete_No_pilha(No_pilha* N){
    free(N->dado);
    free(N);
}

/* IMPLEMENTACOES PILHA */
Pilha* new_Pilha (size_t size){
    Pilha* P = (Pilha*) malloc (sizeof(Pilha));

    void* aux = calloc(1,size);
    P->Topo = new_No_pilha(aux, size);
    free(aux);

    P->Topo->prox = P->Topo->ant = P->Topo;

    P->tam = 0;
    P->size = size;

    return P;

}
void delete_Pilha (Pilha *P){
    clear_Pilha(P);
    delete_No_pilha(P->Topo);
    free(P);
}

No_pilha* push_Pilha (Pilha *P, void* elem){
    if(P == NULL) return NULL;
    if(elem == NULL) return NULL;

    No_pilha* No_pilhavo = new_No_pilha(elem, P->size);
    No_pilhavo->prox = P->Topo->prox;
    No_pilhavo->ant = P->Topo;
    P->Topo->prox->ant = No_pilhavo;
    P->Topo->prox = No_pilhavo;

    P->tam++;

    return No_pilhavo;
}

No_pilha* pop_Pilha (Pilha *P){
    if(P == NULL) return NULL;
    if(P->tam == 0) return NULL;

    No_pilha* pos = P->Topo->prox;
    pos->ant->prox = pos->prox ;
    pos->prox->ant = pos->ant ;

    pos->prox = pos->ant = NULL;

    P->tam--;

    return pos;
}


void clear_Pilha (Pilha* P){
    No_pilha* aux = pop_Pilha(P);
    while(aux != NULL){
        delete_No_pilha(aux);
        aux = pop_Pilha(P);
    }
}

void _reverse_Pilha(Pilha* P){
    No_pilha* aux = pop_Pilha(P);
    if(aux != NULL){
        _reverse_Pilha(P);

        // Insere No_pilha fim
        No_pilha* No_pilhavo = new_No_pilha(aux->dado, aux->size);
        No_pilhavo->prox = P->Topo;
        No_pilhavo->ant = P->Topo->ant;
        P->Topo->ant->prox = No_pilhavo;
        P->Topo->ant = No_pilhavo;

        delete_No_pilha(aux);
        
        P->tam++;
    }  
}

void reverse_Pilha (Pilha* P){
    Pilha* P2 = new_Pilha(P->size);    // Simula uma recursão
    copy_Pilha(P2, P);
    clear_Pilha(P);
    
    No_pilha* aux ;
    aux = pop_Pilha(P2);
    while(aux != NULL){
        push_Pilha(P, aux->dado);
        delete_No_pilha(aux);
        aux = pop_Pilha(P2);
    }
}

void copy_Pilha (Pilha *dest, const Pilha* fonte){
    if(dest == NULL || fonte == NULL) return ;
    if(dest->size != fonte->size) return;
    if(dest->tam != 0) {
        clear_Pilha(dest);
    }
    No_pilha* aux = fonte->Topo->ant;
    while(aux != fonte->Topo){
        push_Pilha(dest, aux->dado);
        aux = aux->ant;
    }
}

void swap_Pilha (Pilha* P1, Pilha *P2){
    if(P1 == NULL || P2 == NULL) return ;
    if(P1->size != P2->size) return;
    Pilha* aux = new_Pilha(P1->size);
    copy_Pilha(aux, P1);
    copy_Pilha(P1, P2);
    copy_Pilha(P2, aux);
}

void print_Pilha (Pilha *P, void(*print)(void*)){
    No_pilha* aux = P->Topo->prox;
    while(aux != P->Topo){
        print(aux->dado);
        aux = aux->prox;
    }
}
