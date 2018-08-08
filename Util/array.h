#ifndef ARRAY
#define ARRAY
#include "tipos_primarios.h"

static double ZERO = 0;

void print_if_array(void *array, size_t length, size_t s, void (*print)(const void *), bool (*condicao)(const void *)); // OK
void print_array(void *array, size_t length, size_t s, void (*print)(const void *));                                    // OK
void printz_array(void *array, size_t length, size_t s, void (*print)(const void *));                                   // OK

void *arrayz(size_t length, size_t s); // OK

void *dup_array(void *array, size_t length, size_t s); // OK

int unique_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

void *shuffle_array(void *array, size_t length, size_t s); // OK

void reverse_array(void *array, size_t length, size_t s); // OK

bool equals_array(void *ar1, void *ar2, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

int find_array(void *array, void *element, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

int max_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK
int min_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *)); // OK

void *resize_array(void *array, size_t length, int new_length, size_t s);         // OK
static void *_resize_array(void *array, size_t length, int new_length, size_t s); // OK

void *remove_if(void *array, size_t length, size_t s, bool (*condicao)(const void *));               // OK
static void *_remove_if_array(void *array, size_t length, size_t s, bool (*condicao)(const void *)); // OK

void *update_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s);         // OK
static void *_update_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s); // OK

/*
 * stdlib.h implementa:
 * 
 * Ordenação:
 * void qsort(void *array, size_t length, size_t size, int (*cmp)(const void *, const void *));
 * 
 * Busca binária:
 * void *bsearch(const void *array, const void *element, size_t length, size_t size, int (*cmp)(const void *, const void *));
 * 
*/

/* INT */
int *random_array(int begin, int end, int n);
int mult_array(int *v, int n);
int sum_array(int *v, int n);

/* FLOAT */
float *random_arrayf(float begin, float end, int n);
float mult_arrayf(float *v, int n);
float sum_arrayf(float *v, int n);

/* DOUBLE */
double *random_arraylf(double begin, double end, int n);
double mult_arraylf(double *v, int n);
double sum_arraylf(double *v, int n);
/* IMPLEMENTAÇÕES */

void print_if_array(void *array, size_t length, size_t s, void (*print)(const void *), bool (*condicao)(const void *))
{
    printf("( ");
    int n = length * s;
    for (int i = 0; i < n && condicao(array + i); i += s)
    {
        print(array + i);
        printf(", ");
    }
    printf(")");
}
void print_array(void *array, size_t length, size_t s, void (*print)(const void *))
{
    bool condicao(const void *element)
    {
        return true;
    }
    print_if_array(array, length, s, print, condicao);
}
void printz_array(void *array, size_t length, size_t s, void (*print)(const void *))
{
    bool condicao(const void *element)
    {
        return toDouble(element) != ZERO;
    }
    print_if_array(array, length, s, print, condicao);
}

void *arrayz(size_t length, size_t s)
{
    return calloc(length, s);
}

void *dup_array(void *array, size_t length, size_t s)
{
    return memcpy(arrayz(length, s), array, length * s);
}

void *copy_array(void *destiny, void *source, size_t length, size_t s)
{
    return memcpy(destiny, source, s * length);
}

int unique_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    /*
     * Este algoritmo busca deixar o array apenas com valores únicos, isto é, sem repetição.
     * Para isto, cada elemento repetido é substituído pelo valor 0.
     * Por fim um vetor auxiliar é criado para posicionar os valores não nulos no início do array recebido.
     * Esta função retorna o novo tamanho do vetor sem as repetições, mas não modifica o seu tamanho
     * original.
     * 
     * Complexidade : n * lg n
    */
    qsort(array, length, s, cmp);
    int n, i, j;
    for (i = n = 0; i < (length - 1) * s; i += s, n++)
    {
        if (EQUAL_TO(cmp(array + i, array + i + s)))
        {
            void *elem = array + i;
            for (i += s; i < length * s && EQUAL_TO(cmp(elem, array + i)); i += s)
                memcpy(array + i, &ZERO, s);
            i -= s;
        }
    }
    if (n < length)
    {
        void *tmp = arrayz(n, s); // MALLOC tmp
        for (i = j = 0; i < length * s; i += s)
        {
            if (NOT_EQUAL_TO(cmp(array + i, &ZERO)))
            {
                memcpy(tmp + j, array + i, s);
                memcpy(array + i, &ZERO, s);
                j += s;
            }
        }
        memcpy(array, tmp, s * n);
        free(tmp); // FREE tmp
    }
    return n;
}

void *shuffle_array(void *array, size_t length, size_t s)
{
    /*
     * Este algoritmo tem o objetivo de embaralhar os valores de um vetor.
     * Para isto, primeiro se embaralha os valores das posições do intervalo [0, n/2],
     * com posições aletórias entre o intervalo [n/2, n].
     * Por fim, embaralha os valores no intervalo [n/2, n], com valores aleatórios no
     * intervalo [0, n/2].
     * 
     * Complexidade : n
    */
    srand((unsigned)time(NULL));
    int range = length / 2;
    int begin = length / 2;
    for (int i = 0; i < (length / 2) * s; i += s)
        swap(array + i, array + s * ((rand() % range) + begin), s);
    begin = 0;
    for (int i = (length - 1) * s; i >= (length / 2) * s; i -= s)
        swap(array + i, array + s * ((rand() % range) + begin), s);

    return array;
}

void reverse_array(void *array, size_t length, size_t s)
{
    for (int i = 0, j = (length - 1) * s; i < j; i += s, j -= s)
        swap(array + i, array + j, s);
}

bool equals_array(void *ar1, void *ar2, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    int n = s * length;
    for (int i = 0; i < n; i += s)
        if (NOT_EQUAL_TO(cmp(ar1 + i, ar2 + i)))
        {
            // printf("\n\n%d %d\n\n", toInt(ar1 + i), toInt(ar2 + i)); // DEBUG
            return false;
        }
    return true;
}

int find_array(void *array, void *element, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    for (int i = 0; i < length; i += s)
        if (EQUAL_TO(cmp(array + i, element)))
            return i / s;
    return -1;
}

int max_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    int max = 0;
    for (int i = 1; i < length; i += s)
        if (GREATER_THAN(cmp(array + i, array + max)))
            max = i;
    return max / s;
}
int min_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    int min = 0;
    for (int i = 1; i < length; i += s)
        if (LESS_THAN(cmp(array + i, array + min)))
            min = i;
    return min / s;
}

// Espero que esses define sejam sempre inline

#define resize_array(array, length, new_length, s) ({array = _resize_array(array, length, new_length, s); array; })
static void *_resize_array(void *array, size_t length, int new_length, size_t s)
{
    void *new = copy_array(arrayz(new_length, s), array, (length < new_length ? length : new_length), s);
    free(array);
    return new;
}

#define remove_if_array(array, length, s, condicao) ({array = _remove_if(array, length, s, condicao); array; })
static void *_remove_if_array(void *array, size_t length, size_t s, bool (*condicao)(const void *))
{
    void *new = arrayz(length, s);
    int n = length * s;
    for (int i = 0, j = 0; i < n; i += s)
        if (!condicao(array + i))
            memcpy(new + j, array + i, s);
    free(array);
    return new;
}

#define update_array(ar1, len1, ar2, len2, s) ({ar1 = _update_array(ar1, len1, ar2, len2, s); ar1; })
static void *_update_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s)
{
    resize_array(ar1, len1, len1 + len2, s);
    copy_array(ar1 + len1 * s, ar2, len2, s);
    return ar1;
}

/* INT */
int *random_array(int begin, int end, int n)
{
    if (begin > end)
        swap(&begin, &end, sizeof(int));

    int *v = arrayz(n, sizeof(int));

    int range = end - begin;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = (rand() % range) + begin;

    return v;
}
int mult_array(int *v, int n)
{
    int m = v[n - 1];
    while (--n)
        m *= v[n - 1];
    return m;
}
int sum_array(int *v, int n)
{
    int s = v[n - 1];
    while (--n)
        s += v[n - 1];
    return s;
}

/* FLOAT */
float *random_arrayf(float begin, float end, int n)
{
    if (begin > end)
        swap(&begin, &end, sizeof(float));

    float *v = arrayz(n, sizeof(float));

    const int MAX = 1e6;

    int range = MAX - (begin / end) * MAX;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = ((rand() * 1000 + rand()) % range) / (float)MAX * end + begin;

    return v;
}
float mult_arrayf(float *v, int n)
{
    float m = v[n - 1];
    while (--n)
        m *= v[n - 1];
    return m;
}
float sum_arrayf(float *v, int n)
{
    float s = v[n - 1];
    while (--n)
        s += v[n - 1];
    return s;
}

/* DOUBLE */
double *random_arraylf(double begin, double end, int n)
{
    if (begin > end)
        swap(&begin, &end, sizeof(double));

    double *v = arrayz(n, sizeof(double));

    const ULLI MAX = 1e16;

    ULLI range = MAX - (begin / end) * MAX;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = (((ULLI)(rand() * 1e12 + rand() * 1e8 + rand() * 1e4 + rand()) % range) / (double)MAX) * end + begin;

    return v;
}
double mult_arraylf(double *v, int n)
{
    double m = v[n - 1];
    while (--n)
        m *= v[n - 1];
    return m;
}
double sum_arraylf(double *v, int n)
{
    double s = v[n - 1];
    while (--n)
        s += v[n - 1];
    return s;
}
#endif