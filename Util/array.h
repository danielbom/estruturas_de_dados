#ifndef ARRAY
#define ARRAY
#include "tipos_primarios.h"

static double ARRAY__ZERO = 0;
// -------------------------------------------- //
//              Funcoes de impressao            //
// -------------------------------------------- //
// Faz a impressão do array enquanto a condição é satisfeita.
void print_if_array(
    void *array,
    size_t length,
    size_t s,
    void (*print)(const void *),
    int (*condicao)(const void *)
    ); // OK
// Faz a impressão do array inteiro.
void print_array(
    void *array,
    size_t length,
    size_t s,
    void (*print)(const void *)
    ); // OK
// Faz a impressão do array inteiro e pula uma linha.
void println_array(
    void *array,
    size_t length,
    size_t s,
    void (*print)(const void *)
    ); // OK
// Faz a impressão do array até o primeiro valor nulo.
void printz_array(
    void *array,
    size_t length,
    size_t s,
    void (*print)(const void *)
    ); // OK
// -------------------------------------------- //
//              Funcoes de criacao              //
// -------------------------------------------- //
// Cria um array de tamanho length do tamanho do tipo s, inicialmente inicializado com zeros.
void *arrayz(
    size_t length,
    size_t s
    ); // OK

// Duplica o array enviado e retorna um ponteiro do resultado.
void *dup_array(
    void *array, 
    size_t length, 
    size_t s
    ); // OK

// Faz uma copia do array [source] para o array [destiny] e retorna o ponteiro de [destiny].
void *copy_array(
    void *destiny, 
    void *source, 
    size_t length, 
    size_t s
    );
// Faz uma copia reversa do array [source] para o array [destiny] e retorna o ponteiro de [destiny].
void *rcopy_array(
    void *destiny, 
    void *source, 
    size_t length, 
    size_t s
    );
// -------------------------------------------- //
//             Funcoes de manipulacao           //
// -------------------------------------------- //
/*
 * Este algoritmo busca deixar o array apenas com
 * valores únicos, isto é, sem repetição.
 * Inicialmente ordena-se o array. Em seguida, com
 * um array auxiliar, iterando sobre o array inicial,
 * ignorando todos os valores repetidos, copia-se 
 * todos os valores unicos.
 * Por fim, o vetor inicial e deletado e substituido
 * pelo vetor auxiliar.
 *
 * Complexidade : n * lg n
*/
// Remove valores duplicados do array.
int unique_array(
    void *array, 
    size_t length, 
    size_t s, 
    int (*cmp)(const void *, const void *)
    ); // OK

/*
 * Este algoritmo tem o objetivo de embaralhar os
 * valores de um vetor.
 * Para isto, primeiro se embaralha os valores das
 * posições do intervalo [0, n/2], com posições
 * aletórias entre o intervalo [n/2, n].
 * Por fim, embaralha os valores no intervalo
 * [n/2, n], com valores aleatórios no intervalo
 * [0, n/2].
 *
 * Complexidade : n
*/
// Embarralha os valores do array.
void *shuffle_array(
    void *array, 
    size_t length, 
    size_t s
    ); // OK

// Inverte a ordem do array e retorna o array.
void *reverse_array(
    void *array, 
    size_t length, 
    size_t s
    ); // OK
// Realoca o array para um novo tamanho.
void *resize_array(
    void **array,
    size_t length,
    int new_length,
    size_t s
    ); // OK
// Desloca o conteudo do array [n_shift * s] bytes para frente.
void *shift_array(
    void **array,
    size_t length,
    int n_shift,
    size_t s
    ); // OK
// Remove os elementos enquanto a condicao for satisfeita.
int remove_if_array(
    void **array,
    size_t length, 
    size_t s, 
    int (*condicao)(const void *)
    ); // TEST
// Concatena o segundo array ao primeiro.
int update_array(
    void *ar1,
    size_t len1,
    void *ar2,
    size_t len2,
    size_t s
    ); // OK
// -------------------------------------------- //
//              Funcoes de busca                //
// -------------------------------------------- //
// Retorna a posição da primeira ocorrencia do elemento no array.
int find_array(
    void *array,
    void *element,
    size_t length,
    size_t s,
    int (*cmp)(const void *, const void *)
    ); // OK

// Retorna a posição da ultima ocorrencia do elemento no array.
int rfind_array(
    void *array, 
    void *element, 
    size_t length, 
    size_t s, 
    int (*cmp)(const void *, const void *)
    ); // OK
// Retorna a posição da primeira ocorrencia do maior valor do array.
int max_array(
    void *array,
    size_t length,
    size_t s,
    int (*cmp)(const void *, const void *)
    ); // OK
// Retorna a posição da primeira ocorrencia do menor valor do array.
int min_array(
    void *array,
    size_t length,
    size_t s,
    int (*cmp)(const void *, const void *)
    ); // OK

// Remove os elementos do array enquanto a condicao for satisfeita.
// -------------------------------------------- //
//          Funcoes de verificacao              //
// -------------------------------------------- //
// Verifica se o array ar1 é igual ao array ar2.
int equals_array(
    void *ar1,
    void *ar2,
    size_t length,
    size_t s,
    int (*cmp)(const void *, const void *)
    ); // OK
// Verifica se o array esta ordenado.
int is_sorted_array(
    void *array, 
    size_t length, 
    size_t size, 
    int (*cmp)(const void*,const void*)
    ); // OK
// Verifica se o array esta ordenado de forma inversa.
int is_reversed_array(
    void *array,
    size_t length,
    size_t size,
    int (*cmp)(const void*,const void*)
    ); // OK
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
// -------------------------------------------- //
//       Funcoes para tipos especificos         //
// -------------------------------------------- //
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



/* Implementacoes array */



/*
 * OBS: print, print_if, println possuem o mesmo código.
 * Caso for alterar, altere todas.
*/
// -------------------------------------------- //
//              Funcoes de impressao            //
// -------------------------------------------- //
void print_if_array(void *array, size_t length, size_t s, void (*print)(const void *), int (*condicao)(const void *))
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
    printf("( ");
    int n = length * s;
    for (int i = 0; i < n; i += s)
    {
        print(array + i);
        printf(", ");
    }
    printf(")");
}
void println_array(void *array, size_t length, size_t s, void (*print)(const void *))
{
    printf("( ");
    int n = length * s;
    for (int i = 0; i < n; i += s)
    {
        print(array + i);
        printf(", ");
    }
    printf(")");
    printf("\n");
}
void printz_array(void *array, size_t length, size_t s, void (*print)(const void *))
{
    int condicao(const void *element)
    {
        return toDouble(element) != ARRAY__ZERO;
    }
    print_if_array(array, length, s, print, condicao);
}
// -------------------------------------------- //
//              Funcoes de criacao              //
// -------------------------------------------- //
void *arrayz(size_t length, size_t s)
{
    return calloc(length, s);
}
void *dup_array(void *array, size_t length, size_t s)
{
    return memcpy(calloc(length, s), array, length * s);
}
void *copy_array(void *destiny, void *source, size_t length, size_t s)
{
    length = length * s ;
    for(int i = 0; i < length; i+=s)
        memcpy(destiny + i, source + i, s);
    return destiny;
}
void *rcopy_array(void *destiny, void *source, size_t length, size_t s)
{
    length = length * s - s;
    for(int i = length; i >= 0; i-=s)
        memcpy(destiny + i, source + i, s);
    return destiny;
}
// -------------------------------------------- //
//             Funcoes de manipulacao           //
// -------------------------------------------- //
int unique_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    qsort(array, length, s, cmp);
    int n, i, j;
    for (i = n = 0; i < (length - 1) * s; i += s, n++)
    {
        if (EQUAL_TO(cmp(array + i, array + i + s)))
        {
            void *value = array + i;
            for (i += s; i < length * s && EQUAL_TO(cmp(value, array + i)); i += s)
                memcpy(array + i, &ARRAY__ZERO, s);
            i -= s;
        }
    }
    if (n < length)
    {
        void *tmp = calloc(n, s); // MALLOC tmp
        for (i = j = 0; i < length * s; i += s)
        {
            if (NOT_EQUAL_TO(cmp(array + i, &ARRAY__ZERO)))
            {
                memcpy(tmp + j, array + i, s);
                memcpy(array + i, &ARRAY__ZERO, s);
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
void *reverse_array(void *array, size_t length, size_t s)
{
    for (int i = 0, j = (length - 1) * s; i < j; i += s, j -= s)
        swap(array + i, array + j, s);
    return array;
}
void *resize_array(void **array, size_t length, int new_length, size_t s)
{
    void *copy = calloc(new_length, s);
    if(length < new_length)
        copy_array(copy, *array, length, s);
    else
        copy_array(copy, *array, new_length, s);
    free(*array);
    *array = copy;
    return copy;
}
void *shift_array(void **array, size_t length, int n_shift, size_t s)
{
    if(n_shift + length < 0)
        return *array;
    
    void *copy = calloc(length + n_shift, s);

    if(n_shift > 0)
        copy_array(copy + n_shift * s, *array, length, s);
    else
        copy_array(copy, *array - n_shift * s, length - n_shift - 1, s);
    
    free(*array);
    *array = copy;
    
    return *array;
}
int remove_if_array(void **array, size_t length, size_t s, int (*condicao)(const void *))
{
    int new_length = 0;
    int n = length * s;
    for (int i = 0; i < n; i += s)
        new_length += !condicao(*array + i);
    
    if(new_length == length) return length;
    if(new_length == 0) 
    {
        free(*array);
        return 0;
    }

    void *new = calloc(new_length, s);
    for (int i = 0, j = 0; i < n; i += s)
    {
        if(!condicao(*array + i))
        {
            memcpy(new + j, *array + i, s);
            j += s;
        }
    }
    
    free(*array);
    *array = new;
    return new_length;
}
int update_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s)
{
    resize_array(ar1, len1, len1 + len2, s);
    copy_array(ar1 + len1 * s, ar2, len2, s);
    return len1 + len2;
}
// -------------------------------------------- //
//              Funcoes de busca                //
// -------------------------------------------- //
int find_array(void *array, void *element, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    length *= s;
    for (int i = 0; i < length; i += s)
        if (EQUAL_TO(cmp(array + i, element)))
            return i / s;
    return -1;
}
int rfind_array(void *array, void *element, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    length *= s;
    for (int i = length - s; i >= 0; i -= s)
        if (EQUAL_TO(cmp(array + i, element)))
            return i / s;
    return -1;
}
int max_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    length *= s;
    int max = 0;
    for (int i = 1; i < length; i += s)
        if (GREATER_THAN(cmp(array + i, array + max)))
            max = i;
    return max / s;
}
int min_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    length *= s;
    int min = 0;
    for (int i = 1; i < length; i += s)
        if (LESS_THAN(cmp(array + i, array + min)))
            min = i;
    return min / s;
}
// -------------------------------------------- //
//          Funcoes de verificacao              //
// -------------------------------------------- //
int equals_array(void *ar1, void *ar2, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    length *= s;
    for(int i = 0; i < length; i += s)
        if(NOT_EQUAL_TO(cmp(ar1 + i, ar2 + i)))
            return 0;
    return 1;
}
int is_sorted_array(void *array, size_t length, size_t size, int (*cmp)(const void*,const void*))
{
    length = length * size;
    for (int i = 1; i < length; i += size)
        if(GREATER_THAN(cmp(array + i, array + i + size)))
            return 0;
    return 1;
}
int is_reversed_array(void *array, size_t length, size_t size, int (*cmp)(const void*,const void*))
{
    length = length * size;
    for (int i = 1; i < length; i += size)
        if(LESS_THAN(cmp(array + i, array + i + size)))
            return 0;
    return 1;
}
// -------------------------------------------- //
//       Funcoes para tipos especificos         //
// -------------------------------------------- //
/* INT */
int *random_array(int begin, int end, int n)
{
    if (begin > end)
        swap(&begin, &end, sizeof(int));

    int *v = calloc(n, sizeof(int));

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

    float *v = calloc(n, sizeof(float));

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

    double *v = calloc(n, sizeof(double));
    int size = sizeof(double);
    const ULLI MAX = 1e16;

    ULLI range = MAX - (begin / end) * MAX;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
        v[i] = (((ULLI)(rand() * 1e10 + rand() * 1e8 + rand() * 1e4 + rand()) % range) / (double)MAX) * end + begin;

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
// -------------------------------------------- //
// Novas funcoes... Talvez sejam apagadas       //
// -------------------------------------------- //
void rearrange_positives_negatives_array(void *array, size_t length, size_t s, int (*cmp)(const void *, const void *))
{
    void *pivo = calloc(1, s);
    length *= s;
    for (int j = 0, i = -s; j < length; j += s)
    {
        if (LESS_THAN(cmp(array + j, pivo)))
        {
            i += s;
            swap(array + j, array + i, s);
        }
    }
}
void merge_sorted_array(void *ar1, size_t len1, void *ar2, size_t len2, size_t s, int (*cmp)(const void *, const void *))
{
    /* NEED TESTS */
    int next_gap(int gap, size_t s)
    {
        return gap > s ? (((gap / 2) + (gap % 2)) / s) * s : 0;
    }
    int i, j;
    len1 *= s;
    len2 *= s;
    int gap = len1 + len2;
    for (gap = next_gap(gap, s); gap; gap = next_gap(gap, gap + s))
    {
        for (i = 0; i + gap < len1; i += s)
            if (GREATER_THAN(cmp(ar1 + i, ar1 + i + gap)))
                swap(ar1 + i, ar1 + i + gap, s);

        for (j = gap > len1 ? gap - len1 : 0; i < len1 && j < len2; j += s, i += s)
            if (GREATER_THAN(cmp(ar1 + i, ar2 + j)))
                swap(ar1 + i, ar2 + j, s);

        if (j < len2)
            for (j = 0; j + gap < len2; j++)
                if (GREATER_THAN(cmp(ar2 + j, ar2 + j + gap)))
                    swap(ar2 + j, ar2 + j + gap, s);
    }
}
#endif
