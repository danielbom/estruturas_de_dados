#include "../tipos_primarios.h"
#include "../Lista.h"
#include "../array_int_simple.h"

bool eh_par_int(void* x){
    int a = *(int*)x;
    return a%2==0 ? true : false;
}

/* Driver program to test functions of Lista.h */
int main(){
    int v[] = {1,2,3,4,5,6,7,8,9,10};
    Lista* L = array_to_Lista(v, 10, sizeof(int)); // MALLOC L
    int v2[] = {5,2,7,4};
    Lista* L2 = array_to_Lista(v2, 4, sizeof(int)); // MALLOC L2

    printf("\nTestando o print_Lista\n");    
    printf("Lista 1: ");
    print_Lista(L, printInt);
    printf("\nTestando a remocao.\n");
    if(remove_Lista(L, &v[4], cmpInt)){
        printf("O valor %d foi removido da lista.\n", v[4]);
        printf("Lista 1: ");
        print_Lista(L, printInt);
    }
    
    printf("\n\nTestando remove_if_Lista.\nRemovendo pares.\n");
    remove_if_Lista(L, eh_par_int);
    print_Lista(L, printInt);
    printf("\n");

    printf("\n\nTeste swap_Lista.\nLista 1: ");
    print_Lista(L, printInt);
    printf("\nLista 2: ");
    print_Lista(L2, printInt);
    printf("\n");
    swap_Lista(L, L2);
    printf("Apos a troca pela funcao swap_Lista.\n");
    printf("Lista 1: ");
    print_Lista(L, printInt);
    printf("\nLista 2: ");
    print_Lista(L2, printInt);
    printf("\n");

    printf("\n\nTeste clear_Lista.\nLista 1: ");
    print_Lista(L, printInt);
    clear_Lista(L);
    printf("\nLista 1: ");
    print_Lista(L, printInt);
    printf("\nTamanho da lista apos o clear: %d\n", L->qtde);

    printf("\n\nTestando delete_Lista para as Listas 1 e 2.\n");
    delete_Lista(&L2);  // FREE L2
    delete_Lista(&L);   // FREE L

    if(L2 == NULL && L == NULL){
        printf("Ponteiros das listas estao nulos.\n");
    }

    printf("\n\nTeste com strings.\n");
    char* str[] = {"ARROZ\0", "BATATA\0", "CENOURA\0", "DIAMANTE\0"};
    L = array_to_Lista(str, 4, sizeof(char*)); // MALLOC L
    printf("Lista 1: ");
    print_Lista(L, printString);
    printf("\n");

    pop_front_Lista(L);
    printf("Removendo o primeiro elemento da Lista 1.\nLista 1: ");    
    print_Lista(L, printString);
    printf("\n");

    delete_Lista(&L);   // FREE L

    int length_array = 15;
    printf("\n\nTestando a funcao sort_Lista.\n");
    int *v3 = random_array(900, 1100, length_array);      // MALLOC v3
    L = array_to_Lista(v3, length_array, sizeof(int));   // MALLOC L

    printf("Array original: ");
    print_array(v3, length_array);

    printf("\nLista original: ");
    print_Lista(L, printInt);

    qsort(v3, length_array, sizeof(int), cmpInt);
    printf("\nArray ordenado: ");
    print_array(v3, length_array);

    sort_Lista(L, cmpInt);
    printf("\nLista ordenada: ");
    print_Lista(L, printInt);

    printf("\n\nTeste is_sorted_Lista.\n");
    if(is_sorted_Lista(L, cmpInt, false)){
        printf("Lista ordenada!\n");
    }

    delete_Lista(&L);   // FREE L
    free(v3);           // FREE v3

    length_array = 60;
    v3 = random_array(0, 15, length_array); // MALLOC v3
    L = array_to_Lista(v3, length_array, sizeof(int)); // MALLOC L
    printf("\n\nTestando funcao unique_Lista para %d itens.", length_array);
    sort_Lista(L, cmpInt);
    printf("\n Lista original: ");
    print_Lista(L, printInt);
    unique_Lista(L, cmpInt);
    printf("\nLista apos func: ");
    print_Lista(L, printInt);
    
    printf("\n\nTestando funcao reverse_Lista.\n");
    reverse_Lista(L);
    print_Lista(L, printInt);
    
    printf("\n\nTestando iterando na Lista.\n");
    for(NoSent* iter = begin_Lista(L); iter != end_Lista(L); next_iter_Lista(&iter)){
        setInt(iter->dado, toInt(iter->dado) * 2);
    }
    print_Lista(L, printInt);
    printf("\n");

    delete_Lista(&L);   // FREE L
    free(v3);           // FREE v3
    system("pause");
    return 0;
}
