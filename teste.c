#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos_primarios.h"
#include "lista.h"
#include "pilha.h"


void teste_Lista(){
    Lista* L = new_Lista(sizeof(unsigned int));
    int v[] = {1,2,3,4,5,6,7,8,9,10};
    for(int i=0; i<10; i++){
        push_back_Lista(L, &v[i]);
    }
    if(remove_Lista(L, &v[4], compararInt)){
        printf("O valor %d existe na minha lista\n", v[4]);
    }
    print_Lista(L, printInt);
    printf("\n");
    printf("%d\n", L->tam);
    clear_Lista(L);
    printf("%d\n", L->tam);

    delete_Lista(L);
    /* TESTE COM STRINGS */
    L = new_Lista(sizeof(char*));
    char* str[15] = {"ARROZ\0", "BATATA\0", "CENOURA\0", "DIAMANTE\0"};
    for(int i = 0; i<4; i++){
        push_back_Lista(L, &str[i]);
    }
    print_Lista(L, printString);
    printf("\n");
    pop_front_Lista(L);
    
    print_Lista(L, printString);
    printf("\n");
    delete_Lista(L);

    delete_Lista(L);
}

void teste_Pilha(){
    Pilha *P = new_Pilha(sizeof(int));
    int v[] = {10,20,30,40,50};
    int n = sizeof(v) / sizeof(int);
    for(int i=0; i<n; i++){
        push_Pilha(P, &v[i]);
    }
    print_Pilha(P, printInt);
    _reverse_Pilha(P);
    printf("\n");

    print_Pilha(P, printInt);
    pop_Pilha(P);
    printf("\n");

    print_Pilha(P, printInt);
    delete_Pilha(P);
    
}

void teste_com_strigs(){
    char* str[15] = {"Macarrao\0"};     // strings necessitam ser no formato **str
    char* str2[15] = {"Melancia\0"};
    char* str3[15] = {"Melancia\0"};
    if(compararString(&str, &str2) == 0){
        printf("Iguais!\n");
    }
    else{
        printf("Diferentes\n");
    }
    if(compararString(&str3, &str2) == 0){
        printf("Iguais!\n");
    }
    else{
        printf("Diferentes\n");
    }
}

/* Driver program to test above function */
int main(){
    teste_Pilha();
    return 0;
}
