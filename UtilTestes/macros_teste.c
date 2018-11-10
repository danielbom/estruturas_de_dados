#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <tgmath.h> // macros para qlqr tipo das funções da biblioteca math.h
//#include <math.h>
#include <stdarg.h>
#include <complex.h>
#include <locale.h>

// Se o primeiro elemento for especificado, os seguintes recebem o incremento a partir deste valor
// Se os valores enum for potencia de 2, é possível criar uma lista de bits
enum week
{
    sunday = 1,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday
};

#define LAMBDA(tipo_retorno) ({ tipo_retorno funcao; })
// _ restante da funcao

#define SWAP(a, b)   \
    do               \
    {                \
        typeof(a) t; \
        t = a;       \
        a = b;       \
        b = t;       \
    } while (0)

#define CMP(a, b) a - b

#define DPRINT(fmt, ...) printf("DEBUG: " fmt "\\n", ##__VA_ARGS__)

#define type_name(T)           \
    _Generic((T),              \
             char              \
             : "char",         \
               int             \
             : "int",          \
               float           \
             : "float" default \
             : "other")

void func(int nb, void (*f)(int))
{
    int i;
    for (i = 0; i < nb; i++)
        f(i);
}

int sum(int n, ...)
{
    va_list vl;
    int soma = 0;

    va_start(vl, n);

    for (int i = 0; i < n; i++)
        soma += va_arg(vl, int);

    va_end(vl);

    return soma;
}

void teste_constantes_macros()
{
    printf("Date: %s\n", __DATE__);
    printf("File: %s\n", __FILE__);
    printf("Time: %s\n", __TIME__);
    //printf("Stdc: %s\n", __STDC__);
    //printf("Line: %s\n", __LINE__);
}

void sizeof_tipos()
{
    printf("sizeof(void*): %d\n", (int)sizeof(void *));
    printf("sizeof(char): %d\n", (int)sizeof(char));
    printf("sizeof(int): %d\n", (int)sizeof(int));
    printf("sizeof(bool): %d\n", (int)sizeof(bool));
    printf("sizeof(long): %d\n", (int)sizeof(long));
    printf("sizeof(float): %d\n", (int)sizeof(float));
    printf("sizeof(double): %d\n", (int)sizeof(double));
    printf("sizeof(unsigned char): %d\n", (int)sizeof(unsigned char));
    printf("sizeof(unsigned int): %d\n", (int)sizeof(unsigned int));
    printf("sizeof(unsigned long long): %d\n", (int)sizeof(unsigned long long));
    printf("sizeof(long long): %d\n", (int)sizeof(long long));
    printf("sizeof(long long int): %d\n", (int)sizeof(long long int));
    printf("sizeof(long double): %d\n", (int)sizeof(long double));
}

void teste_math_h()
{
    // M_E: constante de euler
    printf("e round(e) trunc(e) %lf %lf %lf\n", M_E, round(M_E), trunc(M_E));
}

void teste_SWAP_CMP()
{
    int a = 5;
    int b = 10;
    printf("var_arg sum: %d\n", sum(5, 9, 5, 7, 8, 6));
    printf("SWAP: %d %d\n", a, b);
    SWAP(a, b);
    printf("SWAP: %d %d\n", a, b);
    printf("CMP: %d\n", CMP(a, b));
}

void teste_numero_variado_de_parametros()
{
    int a = 5;
    int b = 10;
    printf("DPRINT: ");
    DPRINT("Valor de a = %d b = %d", a, b);
    printf("\n");
}

void teste_LAMBDA()
{
    printf("Teste funcao LAMBDA\n");

    func(4, LAMBDA(void funcao(int v) {
             printf("%d ", v);
         }));
    printf("\n");

    func(5, ({
             void callback(int v) { printf("%d ", v); }
             callback;
         }));

    printf("\n");
    printf("Teste ");
}

void teste_enum()
{
    printf("Teste enum\n");
    enum week today;
    today = wednesday;
    printf("Day %d\n", today);
}

void mascaras_printf()
{
    unsigned char var = 35;
    printf("Mascaras para o printf:\n");
    printf("Caracter: %c\n", var);
    printf("Decimal: %u\n", var);
    printf("Octal: %o\n", var);
    printf("Hexadecimal: %x\n", var);
}

void teste_operacoes_com_bits()
{
    bool is_set_bit(unsigned char bits, unsigned char mask)
    {
        return (bits & mask) == mask;
    }
    unsigned char set_bit(unsigned char bits, unsigned char maks)
    {
        return bits | maks;
    }
    unsigned char unset_bit(unsigned char bits, unsigned char maks)
    {
        unsigned char all = 0b11111111;
        return bits & (all - maks);
    }
    void print_bin(unsigned char valor)
    {
        for (int i = 0b10000000; i; i >>= 1)
        {
            printf("%d", is_set_bit(valor, i));
        }
    }
    void print_bin_(char *op, int n, ...)
    {
        va_list valores;

        va_start(valores, n);

        for (int i = 0; i < n - 2; i++)
        {
            print_bin(va_arg(valores, int));
            printf(" %s ", op);
        }
        print_bin(va_arg(valores, int));
        printf(" = ");
        print_bin(va_arg(valores, int));
        printf("\n");

        va_end(valores);
    }
    enum bit
    {
        zero = 0b00000000,
        b0 = 0b00000001,
        b1 = 0b00000010,
        b2 = 0b00000100,
        b3 = 0b00001000,
        b4 = 0b00010000,
        b5 = 0b00100000,
        b6 = 0b01000000,
        b7 = 0b10000000,
        all = 0b11111111
    };

    unsigned char a = 0b00000101; // 5
    unsigned char b = 0b00001001; // 9
    unsigned char c = a & b;      // 1
    printf("%x & %x = %x\n", a, b, c);
    print_bin_("&", 3, a, b, c);
}
/*
void teste_complexo()
{
    printf("Teste complexos\n");
    complex float x = 1.0 + 2.0 * I;
    complex float y = x;
    printf("Real: %f\n", creal(x));
    printf("Imaginaria: %f\n", cimag(x));

    complex float z = cpow(x, y);
    printf("Real: %f\n", creal(z));
    printf("Imaginaria: %f\n", cimag(z));
}
*/
int main()
{
    //setlocale(LC_ALL, "Portuguese");
    //teste_constantes_macros();
    //sizeof_tipos();
    //teste_complexo();
    //teste_math_h();
    //teste_enum();
    //mascaras_printf();
    //teste_operacoes_com_bits();
    system("pause");
    return 0;
}