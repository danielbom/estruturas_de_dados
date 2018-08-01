#include "tipos_primarios.h"

ULLI fatorial(ULLI n)
{
    ULLI x = n;
    while (--n)
        x *= n;
    return x;
}