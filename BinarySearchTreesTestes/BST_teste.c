#include "../BinarySearchTrees/BST.h"
#include "../array.h"

/* Driver program to test functions of BST.h */

void printing(BST *B)
{
    printf(" in_order: ");
    in_order_BST(B, printInt);
    printf("\npre_order: ");
    pre_order_BST(B, printInt);
    printf("\npos_order: ");
    pos_order_BST(B, printInt);
}

int main()
{
    int tam = 75;
    BST *B = new_BST(sizeof(int));      // MALLOC B
    int *v = random_array(1, 200, tam); // MALLOC v

    for (int i = 0; i < tam; i++)
        add_BST(B, &v[i], cmpInt);

    printing(B);
    remove_BST(B, &v[tam / 2], cmpInt);

    printf("\nRemovendo %d \n", v[tam / 2]);
    printing(B);

    printf("\n\nTeste clear_BST.\n");
    clear_BST(B);
    if (empyt_BST(B))
    {
        printf("BST esta vazia.\n");
    }
    free(v);        // FREE v
    delete_BST(&B); // FREE B
    system("pause");
    return 0;
}