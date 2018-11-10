#include "../EstruturasDeDados/Queue.h"
#include "../Util/array.h"

/* Driver program to test functions of Queue.h */
int main()
{
    int n = 10;
    int *v = random_array(1, 900, n); // MALLOC v
    Queue *F = new_Queue(sizeof(int));  // MALLOC F

    for (int i = 0; i < n; i++)
    {
        void* new = malloc(sizeof(int));
        memcpy(new, &v[i], sizeof(int));
        push_Queue(F, new);
    }

    print_Queue(F, printInt);

    reverse_Queue(&F);

    printf("\n");

    print_Queue(F, printInt);
    pop_Queue(F);
    printf("\n");

    print_Queue(F, printInt);

    free(v);          // FREE v
    delete_Queue(&F); // FREE F

    return 0;
}
