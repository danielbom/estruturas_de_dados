#ifndef tipos_primarios
#define tipos_primarios

#include <stdio.h>  // printf
#include <stdlib.h> // malloc, talvez nao necessario
#include <string.h> // strcmp
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#ifndef ULLI
#define ULLI unsigned long long int
#endif

#ifndef IS_DIVISIBLE
#define IS_DIVISIBLE(x, y) x % y == 0
#endif

#define EQUAL_TO(comparator) (comparator) == 0
#define NOT_EQUAL_TO(comparator) (comparator) != 0

#define GREATER_THAN(comparator) (comparator) > 0
#define LESS_THAN(comparator) (comparator) < 0

#define GREATER_OR_EQUAL_TO(comparator) (comparator) >= 0
#define LESS_OR_EQUAL_TO(comparator) (comparator) <= 0

#define IS_EVEN(number) number % 2 == 0
#define IS_ODD(number) number % 2 == 1

/* Faz a troca dos dados */
void swap(void *a, void *b, size_t s)
{
    void *t = malloc(s);
    memcpy(t, a, s);
    memcpy(a, b, s);
    memcpy(b, t, s);
    free(t);
}

/* Faz a troca das referencias */
void pswap(void **a, void **b)
{
    void *t = *a;
    *a = *b;
    *b = t;
}

/* CASTING PARA TIPOS PRIMARIOS */
int toInt(const void *v)
{
    return *(int *)v;
}
float toFloat(const void *v)
{
    return *(float *)v;
}
double toDouble(const void *v)
{
    return *(double *)v;
}
char toChar(const void *v)
{
    return *(char *)v;
}
char *toString(const void *v)
{
    return *(char **)v;
}
ULLI toULLI(const void *v)
{
    return *(ULLI *)v;
}

/* ATRIBUIÇÕES PARA TIPOS PRIMARIOS */
void setInt(void *a, int b)
{
    memcpy(a, &b, sizeof(int));
}
void setFloat(float *a, float b)
{
    memcpy(a, &b, sizeof(float));
}
void setDouble(double *a, double b)
{
    memcpy(a, &b, sizeof(double));
}
void setChar(char *a, char b)
{
    memcpy(a, &b, sizeof(char *));
}
void setString(char *a, char *b)
{
    strcpy(a, b);
}

/* IMPRESSAO DE TIPOS PRIMARIOS */
void printInt(const void *v)
{
    printf("%d", toInt(v));
}
void printFloat(const void *v)
{
    printf("%f", toFloat(v));
}
void printDouble(const void *v)
{
    printf("%lf", toDouble(v));
}
void printChar(const void *v)
{
    printf("%c", toChar(v));
}
void printString(const void *v)
{
    printf("%s", toString(v));
}
void printULLI(const void *v)
{
    printf("%ull", toULLI(v));
}

/* COMPARACAO DE TIPOS PRIMARIOS */
int cmpInt(const void *a, const void *b)
{
    return toInt(a) - toInt(b);
}
int cmpFloat(const void *a, const void *b)
{
    float _a = toFloat(a);
    float _b = toFloat(b);
    return _a > _b ? 1 : (_a < _b ? -1 : 0);
}
int cmpDouble(const void *a, const void *b)
{
    float _a = toDouble(a);
    float _b = toDouble(b);
    return _a > _b ? 1 : (_a < _b ? -1 : 0);
}
int cmpChar(const void *a, const void *b)
{
    return toChar(a) - toChar(b);
}
int cmpString(const void *a, const void *b)
{
    return strcmp(toString(a), toString(b));
}
int cmpULLI(const void *a, const void *b)
{
    ULLI _a = toULLI(a);
    ULLI _b = toULLI(b);
    return _a > _b ? 1 : (_a < _b ? -1 : 0);
}

#endif