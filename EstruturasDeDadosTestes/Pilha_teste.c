#include "../EstruturasDeDados/Stack.h"
#include "../Util/array.h"

/* Driver program to test functions of stack.h */
int main()
{
    int n = 50;
    int *v = random_array(1, 900, n);  // MALLOC v
    stack *P = new_stack(sizeof(int)); // MALLOC P

    for (int i = 0; i < n; i++)
    {
        void* new = malloc(sizeof(int));
        memcpy(new, &v[i], sizeof(int));
        push_stack(P, new);
    }

    printf("\n");
    print_stack(P, printInt);
    printf("\n");

    reverse_stack(&P);

    printf("\n");
    print_stack(P, printInt);
    printf("\n");

    pop_stack(P);
    printf("\n");
    print_stack(P, printInt);
    printf("\n");

    free(v);          // FREE v
    delete_stack(&P); // FREE P

    //system("pause");
    return 0;
}
