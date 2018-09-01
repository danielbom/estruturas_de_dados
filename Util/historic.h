/* Historico de strings com no maximo 10 elementos. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *HISTORIC[10] = {0};
int index_historic = 0;
int length_historic = 10;

void add_historic(char *value)
{
    free(HISTORIC[index_historic]);
    HISTORIC[index_historic] = strdup(value);
    index_historic++;
    index_historic %= length_historic;
}

char *get_historic(int pos)
{
    int i = index_historic - pos - 1;
    return HISTORIC[(length_historic + i) % length_historic];
}

void free_historic()
{
    for (int i = 0; i < length_historic; i++)
        free(HISTORIC[i]);
}

void print_historic()
{
    for (int i = 0; i < length_historic && HISTORIC[i]; i++)
        printf("%d: %s\n", i, get_historic(i));
}