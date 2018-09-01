#include "../Util/bitwise.h"
#include <time.h>

int main()
{

    bit64 num = 1024;
    char *bit = to_bin_64(num);

    printBin64(num);
    printf("\n%d\n", strlen(bit));

    free(bit);

    return 0;
}