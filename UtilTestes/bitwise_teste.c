#include "../Util/bitwise.h"
#include <time.h>

void t()
{
    for(int i = -128; i < 128; i++)
    {
        printBin8(i);
        printf("\n");
    }
}

int main()
{

    bit64 num = 1024;
    char *bit = to_bin_64(num);

    printBin64(num);
    printf("\n%d\n", strlen(bit));

    free(bit);

    t();
    return 0;
}