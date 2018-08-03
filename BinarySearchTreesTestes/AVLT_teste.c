#include "../BinarySearchTrees/AVLT.h"
#include "../array.h"

void printing(AVLT *A)
{
    printf(" in_order: ");
    in_order_AVLT(A, printInt);
    printf("\npre_order: ");
    pre_order_AVLT(A, printInt);
    printf("\npos_order: ");
    pos_order_AVLT(A, printInt);
}

int main()
{
    int tam = 20;
    AVLT *A = new_AVLT(sizeof(int));    // MALLOC A
    int *v = random_array(1, 200, tam); // MALLOC v

    for (int i = 0; i < tam; i++)
        add_AVLT(A, &v[i], cmpInt);

    printing(A);
    remove_AVLT(A, &v[tam / 2], cmpInt);

    printf("\nRemovendo %d\n", v[tam / 2]);
    printing(A);

    printf("\n\nTeste clear_AVLT.\n");
    clear_AVLT(A);
    if (empyt_AVLT(A))
        printf("AVLT esta vazia.\n");

    free(v);         // FREE v
    delete_AVLT(&A); // FREE A
    system("pause");

    return 0;
}