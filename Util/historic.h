/* Historico de strings com no maximo 10 elementos. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *HISTORIC[10] = {0};
int index_historic = 0;
int length_historic = 10;

void add_historic(char *value); // Adiciona um valor ao historico
char *get_historic(int pos);    // Recupera um valor do historico, dado uma posicao
void free_historic();           // Libera os espaços alocados com o historico
void print_historic();          // Imprime o estado atual do historico

void add_historic(char *value)
{
    free(HISTORIC[index_historic]);                          // Liberando o espaço para adicionar um item.
    HISTORIC[index_historic] = strdup(value);                // Adicionando
    index_historic = (index_historic + 1) % length_historic; // Incremento
}

char *get_historic(int pos)
{
    int i = index_historic - pos - 1;                         // Buscando a posição do index
    return HISTORIC[(length_historic + i) % length_historic]; // Retornando o resultado
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