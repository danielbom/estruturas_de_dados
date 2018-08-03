#include "../EstruturasDeDados/Fila.h"
#include "../Util/array.h"

/* Driver program to test functions of Fila.h */
int main()
{
    int n = 10;
    int *v = random_array(1, 900, n); // MALLOC v
    Fila *F = new_Fila(sizeof(int));  // MALLOC F

    for (int i = 0; i < n; i++)
    {
        push_Fila(F, &v[i]);
    }

    print_Fila(F, printInt);

    reverse_Fila(&F);

    printf("\n");

    print_Fila(F, printInt);
    pop_Fila(F);
    printf("\n");

    print_Fila(F, printInt);

    free(v);         // FREE v
    delete_Fila(&F); // FREE F

    system("pause");
    return 0;
}
