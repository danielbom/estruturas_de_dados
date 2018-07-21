#include "NoTree.h"

/*
    BST -> BinarySearchTree
*/
typedef struct BST {
    NoTree* raiz;
    int qtde;
    size_t size;
} BST;

/* CONSTRUTOR E DESTRUTOR */
BST* new_BST(size_t size); // OK
void delete_BST(BST** B);

/* FUNCOES DE BUSCA */
NoTree* search_BST(BST* B, void* elem, int(*cmp)(const void*,const void*)); // OK
static NoTree* _search_BST(NoTree* no, void* elem, int(*cmp)(const void*,const void*)); // OK

/* FUNCOES DE INSERCAO */
void add_BST(BST* B, void* elem, int(*cmp)(const void*,const void*)); // OK
static NoTree* _add_BST(BST* B, NoTree** no, void* elem, int(*cmp)(const void*,const void*)); // OK

/* FUNCOES DE REMOCAO */
void remove_BST(BST* B, void* elem, int(*cmp)(const void*,const void*)); // OK
static NoTree* _remover_BST(BST* B, NoTree** no, void* elem, int(*cmp)(const void*,const void*)); // OK

void clear_BST (BST* L); // OK
static NoTree* _clear_BST (NoTree** no); // OK

/* FUNCOES AUXILIARES */
bool empyt_BST(BST* B); // OK
void in_order_BST(BST* B, void(*print)(const void*)); // OK
static void _in_order_BST(NoTree* no, void(*print)(const void*)); // OK
void pre_order_BST(BST* B, void(*print)(const void*)); // OK
static void _pre_order_BST(NoTree* no, void(*print)(const void*)); // OK
void pos_order_BST(BST* B, void(*print)(const void*)); // OK
static void _pos_order_BST(NoTree* no, void(*print)(const void*)); // OK
void copy_BST (BST* dest, const BST* fonte, int(*cmp)(const void*,const void*)); // OK
static void _copy_BST(BST* dest, NoTree* no, int(*cmp)(const void*,const void*)); // OK
void swap_BST (BST* L1, BST* L2);

/* IMPLEMENTACOES BST */

/* CONSTRUTOR E DESTRUTOR */
BST* new_BST(size_t size){
    BST* B = (BST*) malloc (sizeof(BST));
    B->raiz   = NULL;
    B->qtde   = 0;
    B->size   = size;
    return B;
}
void delete_BST(BST** B){
    clear_BST(*B);
    free(B);
    B = NULL;
}

/* FUNCOES DE BUSCA */
NoTree* search_BST(BST* B, void* elem, int(*cmp)(const void*,const void*)){
    return _search_BST(B->raiz, elem, cmp);
}
static NoTree* _search_BST(NoTree* no, void* elem, int(*cmp)(const void*,const void*)){
    if(no == NULL) return NULL;
    if(cmp(elem, no->dado) > 0) return _search_BST(no->dir, elem, cmp);
    if(cmp(elem, no->dado) < 0) return _search_BST(no->esq, elem, cmp);
    return no;
}

/* FUNCOES DE INSERCAO */
void add_BST(BST* B, void* elem, int(*cmp)(const void*,const void*)){
    B->raiz = _add_BST(B, &(B->raiz), elem, cmp);
}
static NoTree* _add_BST(BST* B, NoTree** no, void* elem, int(*cmp)(const void*,const void*)){
    if(*no == NULL){
        *no = new_NoTree(elem, B->size);
        B->qtde++;
    }
    else if(cmp(elem, (*no)->dado) < 0){
        (*no)->esq = _add_BST(B, &((*no)->esq), elem, cmp);
    }
    else if(cmp(elem, (*no)->dado) > 0){
        (*no)->dir = _add_BST(B, &((*no)->dir), elem, cmp);
    }
    return *no;
}

/* FUNCOES DE REMOCAO */
void remove_BST(BST* B, void* elem, int(*cmp)(const void*,const void*)){
    B->raiz = _remover_BST(B, &(B->raiz), elem, cmp);
}
static NoTree* _remover_BST(BST* B, NoTree** no, void* elem, int(*cmp)(const void*,const void*)){
    if(*no == NULL){
        return NULL;
    }
    // Movimentando
    if(cmp(elem, (*no)->dado) < 0){
        (*no)->esq = _remover_BST(B, &((*no)->esq), elem, cmp);
        return *no;
    }
    if(cmp(elem, (*no)->dado) > 0){
        (*no)->dir = _remover_BST(B, &((*no)->dir), elem, cmp);
        return *no;    
    }

    // Removendo
    if((*no)->dir == NULL && (*no)->esq == NULL){
        delete_NoTree(no);
        B->qtde--;
        return NULL;
    }
    if((*no)->dir == NULL && (*no)->esq != NULL){
        NoTree* esq = (*no)->esq;
        delete_NoTree(no);
        B->qtde--;
        return esq;
    }
    if((*no)->dir != NULL && (*no)->esq == NULL){
        NoTree* dir = (*no)->dir;
        delete_NoTree(no);
        B->qtde--;
        return dir;
    }

    NoTree *aux = (*no)->dir;
    while(aux->esq != NULL) aux = aux->esq;

    copy_NoTree(*no, aux);
    (*no)->dir = _remover_BST(B, &((*no)->dir), (*no)->dado, cmp);
    return *no;
}

void clear_BST (BST* L){
    L->raiz = _clear_BST(&(L->raiz));
    L->qtde = 0;
}
static NoTree* _clear_BST (NoTree** no){
    if(*no != NULL){
        (*no)->esq = _clear_BST(&((*no)->esq));
        (*no)->dir = _clear_BST(&((*no)->dir));
        delete_NoTree(no);
    }
    return NULL;
}

/* FUNCOES AUXILIARES */
bool empyt_BST(BST* B){
    return B->qtde == 0;
}
void in_order_BST(BST* B, void(*print)(const void*)){
    _in_order_BST(B->raiz, print);
}
static void _in_order_BST(NoTree* no, void(*print)(const void*)){
    if(no != NULL){
        _in_order_BST(no->esq, print);
        print(no->dado);
        _in_order_BST(no->dir, print);
    }
}
void pre_order_BST(BST* B, void(*print)(const void*)){
    _pre_order_BST(B->raiz, print);
}
static void _pre_order_BST(NoTree* no, void(*print)(const void*)){
    if(no != NULL){
        print(no->dado);
        _pre_order_BST(no->esq, print);
        _pre_order_BST(no->dir, print);
    }
}
void pos_order_BST(BST* B, void(*print)(const void*)){
    _pos_order_BST(B->raiz, print);
}
static void _pos_order_BST(NoTree* no, void(*print)(const void*)){
    if(no != NULL){
        _pos_order_BST(no->esq, print);
        _pos_order_BST(no->dir, print);
        print(no->dado);
    }
}
void copy_BST (BST* dest, const BST* fonte, int(*cmp)(const void*,const void*)){
    if(dest->size == fonte->size){
        _copy_BST(dest, fonte->raiz, cmp);
    }
}
static void _copy_BST(BST* dest, NoTree* no, int(*cmp)(const void*,const void*)){
    if(no != NULL){
        add_BST(dest, no->dado, cmp);
        _copy_BST(dest, no->esq, cmp);
        _copy_BST(dest, no->dir, cmp);
    }
}
