#include "../Util/utilitarios.h"

void printing(char *txt, double value)
{
    printf("%s", txt);
    printSimpleDouble(&value);
    printf("\n");
}

int main()
{
    double n = 10;
    double k = 1;
    double arrj = arrangement(n, k);
    double comb = combination(n, k);

    printing("n: ", n);
    printing("arrj: ", arrj);
    printing("comb: ", comb);

    return 0;
}