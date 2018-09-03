#include "../EstruturasDeDados/list.h"
#include "../Util/array.h"

bool eh_par_int(void *x)
{
    return toInt(x) % 2 == 0 ? true : false;
}
void print_list_ln(char *nome, list *L, void (*print_tipo)(const void *))
{
    printf("%s", nome);
    print_list(L, print_tipo);
    printf("\n");
}

void strings_teste()
{
    printf("\n\nTeste com strings.\n");
    char *str[] = {"ARROZ\0", "BATATA\0", "CENOURA\0", "DIAMANTE\0"};
    list *L = array_to_list(str, 4, sizeof(char *)); // MALLOC L
    print_list_ln("list 1: \0", L, printString);

    pop_front_list(L);
    printf("Removendo o primeiro elemento da list 1.\n");
    print_list_ln("list 1: \0", L, printString);

    delete_list(&L); // FREE L
}

void inicial_e_remocao_teste()
{
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int v2[] = {5, 2, 7, 4};
    list *L = array_to_list(v, 10, sizeof(int));  // MALLOC L
    list *L2 = array_to_list(v2, 4, sizeof(int)); // MALLOC L2

    printf("\nTestando o print_list\n");
    printf("list 1: ");
    print_list(L, printInt);
    printf("\nTestando a remocao.\n");
    if (remove_list(L, &v[4], cmpInt))
    {
        printf("O valor %d foi removido da lista.\n", v[4]);
        printf("list 1: ");
        print_list(L, printInt);
    }

    printf("\n\nTestando remove_if_list.\n");
    printf("Removendo pares.\n");
    remove_if_list(L, eh_par_int);
    print_list(L, printInt);
    printf("\n");

    printf("\n\nTeste swap_list.\n");
    print_list_ln("list 1: ", L, printInt);
    print_list_ln("list 2: ", L2, printInt);
    swap_list(L, L2);
    printf("Apos a troca.\n");
    print_list_ln("list 1: ", L, printInt);
    print_list_ln("list 2: ", L2, printInt);

    printf("\n\nTeste clear_list.\n");
    print_list_ln("list 1: ", L, printInt);
    clear_list(L);
    print_list_ln("list 1: ", L, printInt);
    printf("Tamanho da lista apos o clear: %d\n", L->qtde);

    printf("\n\nTestando delete_list para as lists 1 e 2.\n");
    delete_list(&L2); // FREE L2
    delete_list(&L);  // FREE L

    if (L2 == NULL && L == NULL)
        printf("Ponteiros das listas estao nulos.\n");
}

void auxiliares_teste()
{
    int length_array = 60;
    int *v = random_array(0, 15, length_array);            // MALLOC v
    list *L = array_to_list(v, length_array, sizeof(int)); // MALLOC L
    printf("\n\nTestando funcao unique_list e reverse_list para %d itens.\n", length_array);
    print_list_ln("list original: \0", L, printInt);
    unique_list(L, cmpInt);
    print_list_ln("list apos func: \0", L, printInt);
    reverse_list(L);
    print_list_ln("list invertida: \0", L, printInt);

    printf("\n\nTeste iterando na list.\n");
    for (NoSent *iter = begin_list(L); iter != end_list(L); next_iter_list(&iter))
    {
        setInt(iter->dado, toInt(iter->dado) * 2);
    }
    print_list(L, printInt);
    printf("\n");

    delete_list(&L); // FREE L
    free(v);         // FREE v
}

void ordenacao_teste()
{
    int length_array = 15;
    printf("\n\nTestando a funcao sort_list.\n");
    int *v = random_array(900, 1100, length_array);        // MALLOC v
    list *L = array_to_list(v, length_array, sizeof(int)); // MALLOC L

    printf("Array original: ");
    print_array(v, length_array, sizeof(int), printInt);
    printf("\n");

    print_list_ln("list original: \0", L, printInt);

    qsort(v, length_array, sizeof(int), cmpInt);
    qsort_list(L, cmpInt);

    printf("Array ordenado: ");
    print_array(v, length_array, sizeof(int), printInt);
    printf("\n");

    print_list_ln("list ordenada: \0", L, printInt);

    printf("\n\nTeste is_sorted_list.\n");
    if (is_sorted_list(L, cmpInt))
    {
        printf("list ordenada!\n");
    }
    // Se n >= 1e8 da pau
    // Se n proximo a 2e7 demora cerca de 1 min +/-
    int n = 2e7;
    printf("\n\nTestando a velocidade de ordenacao da lista para %d elementos\n", n);
    L = new_random_int_list(0, n, n); // MALLOC L

    clock_t inicio = clock();
    qsort_list(L, cmpInt);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("lista continua :: tempo gasto: %g\n", tempo);

    if (is_sorted_list(L, cmpInt))
    {
        printf("list ordenada corretamente!\n");
    }

    delete_list(&L); // FREE L

    v = random_array(0, n, n);            // MALLOC v
    L = array_to_list(v, n, sizeof(int)); // MALLOC L

    inicio = clock();
    qsort_list(L, cmpInt);
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("lista fragmentada :: tempo gasto: %g\n", tempo);

    if (is_sorted_list(L, cmpInt))
    {
        printf("list ordenada corretamente!\n");
    }

    inicio = clock();
    qsort(v, n, sizeof(int), cmpInt);
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto qsort: %g\n", tempo);

    free(v);         // FREE v
    delete_list(&L); // FREE L
}

void ordenacao_debug_teste()
{
    int length_array = 4e3;
    printf("\n\nTestando a funcao sort_list com debug.\n");
    printf("count,deep,inicio,fim,fim-inicio\n");
    int *v = random_array(0, 1100, length_array);          // MALLOC v
    list *L = array_to_list(v, length_array, sizeof(int)); // MALLOC L

    sort_list(L, cmpInt);
    printf("\nFim da ordenação\n");
    free(v);         // FREE v
    delete_list(&L); // FREE L
}

/* Driver program to test functions of list.h */
int main()
{
    /*
    auxiliares_teste();
    inicial_e_remocao_teste();
    strings_teste();
    ordenacao_teste();
    */
    ordenacao_debug_teste();
    system("pause");
    return 0;
}
