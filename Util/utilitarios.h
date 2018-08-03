#include "tipos_primarios.h"

ULLI fatorial(ULLI n);

#define GEN_FIBBONATTI(x) gen_fibbonatti(x)

ULLI gen_fibbonatti(bool run);

/* IMPLEMENTAÇÕES */

ULLI fatorial(ULLI n)
{
    ULLI x = n;
    while (--n)
        x *= n;
    return x;
}

ULLI gen_fibbonatti(bool run)
{
    static ULLI a = 0;
    static ULLI b = 1;
    ULLI r;
    if (run)
    {
        r = a;
        a = b;
        b = a + r;
        return r;
    }
    a = 0;
    b = 1;
}