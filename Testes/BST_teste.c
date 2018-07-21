#include "../tipos_primarios.h"
#include "../BST.h"
#include "../array_int_simple.h"

/* Driver program to test functions of BST.h */
int main(){
    int tam = 75;
    BST* A = new_BST(sizeof(int)); // MALLOC
    int *v = random_array(1,200,tam);

    for(int i = 0; i < tam; i++)
        add_BST(A, &v[i], cmpInt);

    printf(" in_order: ");
    in_order_BST(A, printInt);
    printf("\npre_order: ");
    pre_order_BST(A, printInt);
    printf("\npos_order: ");
    pos_order_BST(A, printInt);

    printf("\n\nTeste clear_BST.\n");
    clear_BST(A);
    if(empyt_BST(A)){
        printf("BST esta vazia.\n");
    }
    free(v);
    delete_BST(&A); // FREE
    system("pause");
    return 0;
}