#include "../tipos_primarios.h"
#include "../Pilha.h"
#include "../array_int_simple.h"

/* Driver program to test functions of Pilha.h */
int main(){
    int n = 50;
    int *v = random_array(1,900, n); // MALLOC v
    Pilha *P = new_Pilha(sizeof(int)); // MALLOC P

    for(int i=0; i<n; i++){
        push_Pilha(P, &v[i]);
    }

    print_Pilha(P, printInt);

    reverse_Pilha(&P);
    
    printf("\n");

    print_Pilha(P, printInt);
    pop_Pilha(P);
    printf("\n");

    print_Pilha(P, printInt);
    
    free(v);    // FREE v
    delete_Pilha(&P);   // FREE P

    system("pause");
    return 0;
}
