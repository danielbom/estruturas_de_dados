/* Historico de strings com no maximo 10 elementos. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *HISTORIC[10] = {0};
int i_historic = 0;
int len_historic = 10;

void add_historic(char *value)
{
    free(HISTORIC[i_historic]);
    HISTORIC[i_historic % len_historic] = strdup(value);
    i_historic = (i_historic + 1) % len_historic;
}

char *get_historic(int pos)
{
    return HISTORIC[(pos - i_historic + len_historic) % len_historic];
}

void free_historic()
{
    for (int i = 0; i < len_historic; i++)
        free(HISTORIC[i]);
}

void print_historic()
{
    for (int i = i_historic, j = 0; j < len_historic; j++, i++)
        printf("%d : %s\n", (i - i_historic + len_historic) % len_historic, HISTORIC[i % len_historic]);
}