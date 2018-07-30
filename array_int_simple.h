#ifndef array_int_simple
#define array_int_simple

#include "tipos_primarios.h"
#include <time.h>

void print_if_array(int *v, int n, bool (*condicao)(int));
void print_array(int *v, int n);

int *random_array(int begin, int end, int array_length);
int *zeros_array(int array_length);

int *copy_array(int *v, int n);

int unique_array(int *v, int n);

bool equals_array(int *v1, int *v2, int n);
int find_array(int *v, int n, int e);
int max_array(int *v, int n);
int min_array(int *v, int n);

int mult_array(int *v, int n);
int sum_array(int *v, int n);

int *random_array(int begin, int end, int array_length)
{
    if (begin > end)
        swap(&begin, &end, sizeof(int));

    int *v = (int *)malloc(array_length * sizeof(int));

    int range = end - begin;

    srand((unsigned)time(NULL));
    for (int i = 0; i < array_length; i++)
        v[i] = (rand() % range) + begin;

    return v;
}

void print_if_array(int *v, int n, bool (*condicao)(int))
{
    printf("( ");
    for (int i = 0; i < n && condicao(v[i]); i++)
        printf("%d, ", v[i]);
    printf(")");
}

bool equals_array(int *v1, int *v2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (v1[i] != v2[i])
        {
            // DEBUG
            // printf("\n\n%d %d\n\n", v1[i], v2[i]);
            return false;
        }
    }
    return true;
}

bool equals_array_(void *a, void *b, int n, int (*cmp)(const void *, const void *))
{
    for (int i = 0; i < n; i++)
    {
        if (NOT_EQUAL_TO(cmp(a + i, b + i)))
        {
            // DEBUG
            // printf("\n\n%d %d\n\n", v1[i], v2[i]);
            return false;
        }
    }
    return true;
}

int find_array(int *v, int n, int e)
{
    for (int i = 0; i < n; i++)
        if (v[i] == e)
            return i;
    return -1;
}

int *zeros_array(int array_length)
{
    return (int *)calloc(array_length, sizeof(int));
}

void printz_array(int *v, int n)
{
    printf("( ");
    for (int i = 0; i < n && v[i]; i++)
        printf("%d, ", v[i]);
    printf(")");
}

void print_array(int *v, int n)
{
    printf("( ");
    for (int i = 0; i < n; i++)
        printf("%d, ", v[i]);
    printf(")");
}

int unique_array(int *v, int n)
{
    int _unique_array(int *v, int n)
    {
        int i, j;
        for (i = 0; i < n; i++)
        {
            if (v[i] == v[i + 1])
            {
                n--;
                for (j = i + 1; j < n; j++)
                    v[j] = v[j + 1];
                v[n] = 0;
            }
        }
        return n;
    }

    qsort(v, n, sizeof(int), cmpInt);

    int i, j;
    for (i = 0; i < n; i++)
    {
        if (v[i] == v[i + 1])
        {
            n--;
            for (j = i + 1; j < n; j++)
                v[j] = v[j + 1];
            v[j] = 0;
        }
    }
    return _unique_array(v, n);
}

int *copy_array(int *v, int n)
{
    int *r = (int *)calloc(n, sizeof(int));
    memcpy(r, v, n * sizeof(int));
    return r;
}

int max_array(int *v, int n)
{
    int max = 0;
    for (int i = 1; i < n; i++)
        if (v[max] < v[i])
            max = i;
    return max;
}

int min_array(int *v, int n)
{
    int min = 0;
    for (int i = 1; i < n; i++)
        if (v[min] > v[i])
            min = i;
    return min;
}

int mult_array(int *v, int n)
{
    int m = 1;
    for (int i = 0; i < n; i++)
        m *= v[i] ? v[i] : 1;
    return m;
}

int sum_array(int *v, int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += v[i];
    return s;
}

#endif