#ifndef ARRAY
#define ARRAY

#include "tipos_primarios.h"
#include <time.h>

void print_if_array(void *array, int length, size_t s, void (*print)(const void *), bool (*condicao)(const void *)); // OK
void print_array(void *array, int length, size_t s, void (*print)(const void *));                                    // OK
void printz_array(void *array, int length, size_t s, void (*print)(const void *));                                   // OK

void *arrayz(int length, size_t s); // OK

void *dup_array(void *array, int length, size_t s); // OK

int unique_array(void *array, int length, size_t s, int (*cmp)(const void *, const void *)); // OK

void *shuffle_array(void *array, int length, size_t s); // OK

bool equals_array(void *ar1, void *ar2, int length, size_t s, int (*cmp)(const void *, const void *));    // OK
int find_array(void *array, int length, void *element, size_t s, int (*cmp)(const void *, const void *)); // OK
int max_array(void *array, int length, size_t s, int (*cmp)(const void *, const void *));                 // OK
int min_array(void *array, int length, size_t s, int (*cmp)(const void *, const void *));                 // OK

/* IMPLEMENTAÇÕES */

void print_if_array(void *array, int length, size_t s, void (*print)(const void *), bool (*condicao)(const void *))
{
    printf("( ");
    for (int i = 0; i < length * s && condicao(array + i); i += s)
    {
        print(array + i);
        printf(", ");
    }
    printf(")");
}
void print_array(void *array, int length, size_t s, void (*print)(const void *))
{
    bool condicao(const void *element)
    {
        return true;
    }
    print_if_array(array, length, s, print, condicao);
}
void printz_array(void *array, int length, size_t s, void (*print)(const void *))
{
    bool condicao(const void *element)
    {
        return toDouble(element) != 0;
    }
    print_if_array(array, length, s, print, condicao);
}

void *arrayz(int length, size_t s)
{
    return calloc(length, s);
}

void *dup_array(void *array, int length, size_t s)
{
    void *new = calloc(length, s);
    memcpy(new, array, length * s);
    return new;
}

int unique_array(void *array, int length, size_t s, int (*cmp)(const void *, const void *))
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
    int zero = 0;
    for (i = n = 0; i < (length - 1) * s; i += s, n++)
    {
        if (EQUAL_TO(cmp(array + i, array + i + s)))
        {
            void *elem = array + i;
            for (i += s; i < length * s && EQUAL_TO(cmp(elem, array + i)); i += s)
                memcpy(array + i, &zero, s);
            i -= s;
        }
    }
    if (n < length)
    {
        void *tmp = arrayz(n, s); // MALLOC tmp
        for (i = j = 0; i < length * s; i += s)
        {
            if (NOT_EQUAL_TO(cmp(array + i, &zero)))
            {
                memcpy(tmp + j, array + i, s);
                memcpy(array + i, &zero, s);
                j += s;
            }
        }
        memcpy(array, tmp, s * n);
        free(tmp); // FREE tmp
    }
    return n;
}

void *shuffle_array(void *array, int length, size_t s)
{
    /*
     * Este algoritmo tem o objetivo de embaralhar os valores de um vetor.
     * Para isto, primeiro se embaralha os valores das posições pares no intervalo [0, n/2],
     * com posições aletórias entre o intervalo [n/2, n].
     * Depois, embaralha os valores das posições impares no intervalo [0, n/2], com posições
     * aleatórias entre o intervalo [n/2, n].
     * O processo se repete para valores a uma distancia par no intervalo [n/2, n], com posições
     * aleatórias entre o intervalo [0, n/2], e por fim, para os valores a uma distancia par no
     * intervalo [n/2 + 1, n], com valores aleatórios no intervalo [0, n/2].
     * 
     * Complexidade : n
    */
    srand((unsigned)time(NULL));
    int range = length / 2;
    int begin = length / 2;
    for (int i = 0; i < (length / 2) * s; i += 2 * s)
        swap(array + i, array + s * ((rand() % range) + begin), s);
    for (int i = s; i < (length / 2) * s; i += 2 * s)
        swap(array + i, array + s * ((rand() % range) + begin), s);

    begin = 0;
    for (int i = (length - 1) * s; i >= (length / 2) * s; i -= 2 * s)
        swap(array + i, array + s * ((rand() % range) + begin), s);
    for (int i = (length - 2) * s; i >= (length / 2) * s; i -= 2 * s)
        swap(array + i, array + s * ((rand() % range) + begin), s);

    return array;
}

bool equals_array(void *ar1, void *ar2, int length, size_t s, int (*cmp)(const void *, const void *))
{
    for (int i = 0; i < length; i += s)
        if (NOT_EQUAL_TO(cmp(ar1 + i, ar2 + i)))
            return false;
    return true;
}

int find_array(void *array, int length, void *element, size_t s, int (*cmp)(const void *, const void *))
{
    for (int i = 0; i < length; i += s)
        if (EQUAL_TO(cmp(array + i, element)))
            return i / s;
    return -1;
}

int max_array(void *array, int length, size_t s, int (*cmp)(const void *, const void *))
{
    int max = 0;
    for (int i = 1; i < length; i += s)
        if (GREATER_THAN(cmp(array + i, array + max)))
            max = i;
    return max / s;
}
int min_array(void *array, int length, size_t s, int (*cmp)(const void *, const void *))
{
    int min = 0;
    for (int i = 1; i < length; i += s)
        if (LESS_THAN(cmp(array + i, array + min)))
            min = i;
    return min / s;
}

#endif