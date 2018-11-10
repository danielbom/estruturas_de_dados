#include "../EstruturasDeDados/List.h"
#include "../Util/array.h"

bool eh_par_int(void *x)
{
    return toInt(x) % 2 == 0 ? true : false;
}
void print_List_ln(char *nome, List *L, void (*print_tipo)(const void *))
{
    printf("%s", nome);
    print_List(L, print_tipo);
    printf("\n");
}

void strings_teste()
{
    printf("\n\nTeste com strings.\n");
    char *str[] = {"ARROZ\0", "BATATA\0", "CENOURA\0", "DIAMANTE\0"};
    List *L = array_to_List(str, 4, sizeof(char *)); // MALLOC L
    print_List_ln("List 1: \0", L, printString);

    pop_front_List(L);
    printf("Removendo o primeiro elemento da List 1.\n");
    print_List_ln("List 1: \0", L, printString);

    delete_List(&L); // FREE L
}

void inicial_e_remocao_teste()
{
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int v2[] = {5, 2, 7, 4};
    List *L = array_to_List(v, 10, sizeof(int));  // MALLOC L
    List *L2 = array_to_List(v2, 4, sizeof(int)); // MALLOC L2

    printf("\nTestando o print_List\n");
    printf("List 1: ");
    print_List(L, printInt);
    printf("\nTestando a remocao.\n");
    if (remove_List(L, &v[4], cmpInt))
    {
        printf("O valor %d foi removido da Lista.\n", v[4]);
        printf("List 1: ");
        print_List(L, printInt);
    }

    printf("\n\nTestando remove_if_List.\n");
    printf("Removendo pares.\n");
    remove_if_List(L, eh_par_int);
    print_List(L, printInt);
    printf("\n");

    printf("\n\nTeste swap_List.\n");
    print_List_ln("List 1: ", L, printInt);
    print_List_ln("List 2: ", L2, printInt);
    swap_List(L, L2);
    printf("Apos a troca.\n");
    print_List_ln("List 1: ", L, printInt);
    print_List_ln("List 2: ", L2, printInt);

    printf("\n\nTeste clear_List.\n");
    print_List_ln("List 1: ", L, printInt);
    clear_List(L);
    print_List_ln("List 1: ", L, printInt);
    printf("Tamanho da Lista apos o clear: %d\n", L->qtde);

    printf("\n\nTestando delete_List para as Lists 1 e 2.\n");
    delete_List(&L2); // FREE L2
    delete_List(&L);  // FREE L

    if (L2 == NULL && L == NULL)
        printf("Ponteiros das Listas estao nulos.\n");
}

void auxiliares_teste()
{
    int length_array = 60;
    int *v = random_array(0, 15, length_array);            // MALLOC v
    List *L = array_to_List(v, length_array, sizeof(int)); // MALLOC L
    printf("\n\nTestando funcao unique_List e reverse_List para %d itens.\n", length_array);
    print_List_ln("List original: \0", L, printInt);
    unique_List(L, cmpInt);
    print_List_ln("List apos func: \0", L, printInt);
    reverse_List(L);
    print_List_ln("List invertida: \0", L, printInt);

    printf("\n\nTeste iterando na List.\n");
    for (NoSent *iter = begin_List(L); iter != end_List(L); next_iter_List(&iter))
    {
        setInt(iter->dado, toInt(iter->dado) * 2);
    }
    print_List(L, printInt);
    printf("\n");

    delete_List(&L); // FREE L
    free(v);         // FREE v
}

void ordenacao_teste()
{
    int length_array = 15;
    printf("\n\nTestando a funcao sort_List.\n");
    int *v = random_array(900, 1100, length_array);        // MALLOC v
    List *L = array_to_List(v, length_array, sizeof(int)); // MALLOC L

    printf("Array original: ");
    print_array(v, length_array, sizeof(int), printInt);
    printf("\n");

    print_List_ln("List original: \0", L, printInt);

    qsort(v, length_array, sizeof(int), cmpInt);
    qsort_List(L, cmpInt);

    printf("Array ordenado: ");
    print_array(v, length_array, sizeof(int), printInt);
    printf("\n");

    print_List_ln("List ordenada: \0", L, printInt);

    printf("\n\nTeste is_sorted_List.\n");
    if (is_sorted_List(L, cmpInt))
    {
        printf("List ordenada!\n");
    }
    // Se n >= 1e8 da pau
    // Se n proximo a 2e7 demora cerca de 1 min +/-
    int n = 2e7;
    printf("\n\nTestando a velocidade de ordenacao da Lista para %d elementos\n", n);
    L = new_random_int_List(0, n, n); // MALLOC L

    clock_t inicio = clock();
    qsort_List(L, cmpInt);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Lista continua :: tempo gasto: %g\n", tempo);

    if (is_sorted_List(L, cmpInt))
    {
        printf("List ordenada corretamente!\n");
    }

    delete_List(&L); // FREE L

    v = random_array(0, n, n);            // MALLOC v
    L = array_to_List(v, n, sizeof(int)); // MALLOC L

    inicio = clock();
    qsort_List(L, cmpInt);
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Lista fragmentada :: tempo gasto: %g\n", tempo);

    if (is_sorted_List(L, cmpInt))
    {
        printf("List ordenada corretamente!\n");
    }

    inicio = clock();
    qsort(v, n, sizeof(int), cmpInt);
    fim = clock();

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto qsort: %g\n", tempo);

    free(v);         // FREE v
    delete_List(&L); // FREE L
}

void ordenacao_debug_teste()
{
    int length_array = 4e3;
    printf("\n\nTestando a funcao sort_List com debug.\n");
    printf("count,deep,inicio,fim,fim-inicio\n");
    int *v = random_array(0, 1100, length_array);          // MALLOC v
    List *L = array_to_List(v, length_array, sizeof(int)); // MALLOC L

    sort_List(L, cmpInt);
    printf("\nFim da ordenação\n");
    free(v);         // FREE v
    delete_List(&L); // FREE L
}

/* Driver program to test functions of List.h */
int main()
{
    /*
    auxiliares_teste();
    inicial_e_remocao_teste();
    strings_teste();
    ordenacao_teste();
    */
    ordenacao_debug_teste();
    //system("pause");
    return 0;
}
