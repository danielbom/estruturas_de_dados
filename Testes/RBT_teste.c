#include "../RBT.h"
#include "../array_int_simple.h"
#include <stdio.h>
#include <stdlib.h>

void printing(RBT *RB)
{
    printf(" in_order: ");
    in_order_RBT(RB, printInt);
    printf("\npre_order: ");
    pre_order_RBT(RB, printInt);
    printf("\npos_order: ");
    pos_order_RBT(RB, printInt);
}

int main()
{
    int tam = 20;
    RBT *RB = new_RBT(sizeof(int));     // MALLOC RB
    int *v = random_array(1, 200, tam); // MALLOC v

    for (int i = 0; i < tam; i++)
        add_RBT(RB, &v[i], cmpInt);

    printing(RB);
    remove_RBT(RB, &v[tam / 2], cmpInt);

    printf("\nRemovendo %d\n", v[tam / 2]);
    printing(RB);

    printf("\n\nTeste clear_RBT.\n");
    clear_RBT(RB);
    if (empyt_RBT(RB))
        printf("RBT esta vazia.\n");

    free(v);         // FREE v
    delete_RBT(&RB); // FREE RB
    system("pause");

    return 0;
}