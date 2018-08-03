#include "../EstruturasDeDados/Lista.h"
#include "../Util/array.h"

bool eh_par_int(void *x)
{
    int a = *(int *)x;
    return a % 2 == 0 ? true : false;
}
void print_Lista_ln(char *nome, Lista *L, void (*print_tipo)(const void *))
{
    printf("%s", nome);
    print_Lista(L, print_tipo);
    printf("\n");
}

void strings_teste()
{
    printf("\n\nTeste com strings.\n");
    char *str[] = {"ARROZ\0", "BATATA\0", "CENOURA\0", "DIAMANTE\0"};
    Lista *L = array_to_Lista(str, 4, sizeof(char *)); // MALLOC L
    print_Lista_ln("Lista 1: \0", L, printString);

    pop_front_Lista(L);
    printf("Removendo o primeiro elemento da Lista 1.\n");
    print_Lista_ln("Lista 1: \0", L, printString);

    delete_Lista(&L); // FREE L
}

void inicial_e_remocao_teste()
{
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int v2[] = {5, 2, 7, 4};
    Lista *L = array_to_Lista(v, 10, sizeof(int));  // MALLOC L
    Lista *L2 = array_to_Lista(v2, 4, sizeof(int)); // MALLOC L2

    printf("\nTestando o print_Lista\n");
    printf("Lista 1: ");
    print_Lista(L, printInt);
    printf("\nTestando a remocao.\n");
    if (remove_Lista(L, &v[4], cmpInt))
    {
        printf("O valor %d foi removido da lista.\n", v[4]);
        printf("Lista 1: ");
        print_Lista(L, printInt);
    }

    printf("\n\nTestando remove_if_Lista.\n");
    printf("Removendo pares.\n");
    remove_if_Lista(L, eh_par_int);
    print_Lista(L, printInt);
    printf("\n");

    printf("\n\nTeste swap_Lista.\n");
    print_Lista_ln("Lista 1: \0", L, printInt);
    print_Lista_ln("Lista 2: \0", L2, printInt);
    swap_Lista(L, L2);
    printf("Apos a troca.\n");
    print_Lista_ln("Lista 1: \0", L, printInt);
    print_Lista_ln("Lista 2: \0", L2, printInt);

    printf("\n\nTeste clear_Lista.\n");
    print_Lista_ln("Lista 1: \0", L, printInt);
    clear_Lista(L);
    print_Lista_ln("Lista 1: \0", L, printInt);
    printf("Tamanho da lista apos o clear: %d\n", L->qtde);

    printf("\n\nTestando delete_Lista para as Listas 1 e 2.\n");
    delete_Lista(&L2); // FREE L2
    delete_Lista(&L);  // FREE L

    if (L2 == NULL && L == NULL)
        printf("Ponteiros das listas estao nulos.\n");
}

void auxiliares_teste()
{
    int length_array = 60;
    int *v = random_array(0, 15, length_array);              // MALLOC v
    Lista *L = array_to_Lista(v, length_array, sizeof(int)); // MALLOC L
    printf("\n\nTestando funcao unique_Lista e reverse_Lista para %d itens.\n", length_array);
    print_Lista_ln("Lista original: \0", L, printInt);
    unique_Lista(L, cmpInt);
    print_Lista_ln("Lista apos func: \0", L, printInt);
    reverse_Lista(L);
    print_Lista_ln("Lista invertida: \0", L, printInt);

    printf("\n\nTeste iterando na Lista.\n");
    for (NoSent *iter = begin_Lista(L); iter != end_Lista(L); next_iter_Lista(&iter))
    {
        setInt(iter->dado, toInt(iter->dado) * 2);
    }
    print_Lista(L, printInt);
    printf("\n");

    delete_Lista(&L); // FREE L
    free(v);          // FREE v
}

void ordenacao_teste()
{
    int length_array = 15;
    printf("\n\nTestando a funcao sort_Lista.\n");
    int *v = random_array(900, 1100, length_array);          // MALLOC v
    Lista *L = array_to_Lista(v, length_array, sizeof(int)); // MALLOC L

    printf("Array original: ");
    print_array(v, length_array, sizeof(int), printInt);
    printf("\n");

    print_Lista_ln("Lista original: \0", L, printInt);

    qsort(v, length_array, sizeof(int), cmpInt);
    qsort_Lista(L, cmpInt);

    printf("Array ordenado: ");
    print_array(v, length_array, sizeof(int), printInt);
    printf("\n");

    print_Lista_ln("Lista ordenada: \0", L, printInt);

    printf("\n\nTeste is_sorted_Lista.\n");
    if (is_sorted_Lista(L, cmpInt))
    {
        printf("Lista ordenada!\n");
    }
    // Se n >= 1e8 da pau
    // Se n proximo a 2e7 demora cerca de 1 min +/-
    int n = 2e7;
    printf("\n\nTestando a velocidade de ordenacao da lista para %d elementos\n", n);
    L = new_random_int_Lista(0, n, n); // MALLOC L

    clock_t inicio = clock();
    qsort_Lista(L, cmpInt);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("lista continua :: tempo gasto: %g\n", tempo);

    if (is_sorted_Lista(L, cmpInt))
    {
        printf("Lista ordenada corretamente!\n");
    }

    delete_Lista(&L); // FREE L

    v = random_array(0, n, n);             // MALLOC v
    L = array_to_Lista(v, n, sizeof(int)); // MALLOC L

    inicio = clock();
    qsort_Lista(L, cmpInt);
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("lista fragmentada :: tempo gasto: %g\n", tempo);

    if (is_sorted_Lista(L, cmpInt))
    {
        printf("Lista ordenada corretamente!\n");
    }

    inicio = clock();
    qsort(v, n, sizeof(int), cmpInt);
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto qsort: %g\n", tempo);

    free(v);          // FREE v
    delete_Lista(&L); // FREE L
}

/* Driver program to test functions of Lista.h */
int main()
{
    ordenacao_teste();
    system("pause");
    return 0;
}
