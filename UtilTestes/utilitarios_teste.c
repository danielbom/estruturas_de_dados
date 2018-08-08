#include "../Util/utilitarios.h"

long double fatorial(long double n)
{
    long double x = n;
    while (--n)
        x *= n;
    return x;
}

int main()
{
    long double n = 170;
    long double fact = fatorial(n);
    printLongDouble(&n);
    printf("\n");
    printLongDouble(&fact);
    //printSimpleDouble(&fact);
    //printULLI(&fact);

    return 0;
}