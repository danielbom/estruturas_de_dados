#include "../Util/array.h"

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
void teste_resize()
{
    int *ar = random_array(0, 50, 10);
    print_array(ar, 10, sizeof(int), printInt);
    printf("\n");
    print_array(resize_array((void**)(&ar), 10, 20, sizeof(int)), 20, sizeof(int), printInt);
    printf("\n");
    print_array(resize_array((void**)(&ar), 20, 10, sizeof(int)), 10, sizeof(int), printInt);
    printf("\n");
    free(ar);

}
void teste_shift()
{
    int s = sizeof(int);
    int n = 10;
    int shift = 2;
    int *ar = random_array(0, 50, n);   // MALLOC ar
    printf("\nInitial.\n");
    print_array(ar, n, s, printInt);

    printf("\nFirst shifting.\n");
    shift_array((void**)(&ar), n, shift, s);
    print_array(ar, n + shift, s, printInt);
    n = n + shift;

    printf("\nSecond shifting.\n");
    shift_array((void**)(&ar), n, shift, s);
    print_array(ar, n + shift, s, printInt);
    n = n + shift;
    
    printf("\nThird shifting.\n");
    for(int i = 0; i < 5; i++)
    {
        shift = -1;
        shift_array((void**)(&ar), n, shift, s);
        print_array(ar, n + shift, s, printInt);
        n = n + shift;
        printf("\n");
    }
    free(ar);
}

void teste_random_float()
{
    int n = 10;
    float *r = random_arrayf(0, 1, n);
    printf("\n");
    print_array(r, n, sizeof(float), printFloat);
    printf("\n");
}
void teste_random_double()
{
    int n = 10;
    double *r = random_arraylf(-1, 1, n);
    printf("\n");
    print_array(r, n, sizeof(double), printDouble);
    printf("\n");
}

int main()
{
    teste_shift();
    /*
    teste_float();
    teste_int();
    teste_resize();
    teste_random_float();
    teste_random_double();
    */
    return 0;
}