#include "../array.h"
#include "../array_int_simple.h"

void teste_float()
{
    int (*cmp)(const void *, const void *) = cmpFloat;
    void (*print)(const void *) = printFloat;
    int n = 20;
    size_t s = sizeof(float);
    float *ar = arrayz(n, s); //random_array(5, 10, n); // MALLOC ar

    for (int i = 0; i < n; i++)
        ar[i] = (i % 5) + 5;

    print_array(ar, n, s, print);

    printf("\n%d\n", unique_array(ar, n, s, cmp));

    print_array(ar, n, s, print);
    printf("\n");

    free(ar); // FREE ar
}

void teste_int()
{
    int (*cmp)(const void *, const void *) = cmpInt;
    void (*print)(const void *) = printInt;
    int n = 20;
    size_t s = sizeof(int);
    int *ar = random_array(5, 10, n); // MALLOC ar

    printz_array(ar, n, s, print);

    int nn = unique_array(ar, n, s, cmp);
    printf("\n%d\n", nn);

    printz_array(ar, nn, s, print);
    printf("\n");

    free(ar); // FREE ar
    n = 500;
    ar = arrayz(n, s);

    for (int i = 0; i < n; i++)
        ar[i] = i;
    printf("\n\n");
    print_array(ar, n, s, print);
    printf("\n\n");

    shuffle_array(ar, n, s);

    printf("\n\n");
    print_array(ar, n, s, print);
    printf("\n\n");

    free(ar); // FREE ar
}

int main()
{
    teste_int();
    return 0;
}