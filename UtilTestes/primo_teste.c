#include "../Util/primo.h"

void teste_grande_primo()
{
    ULLI num = 1e9;

    printf("Begin: %.0lf\n", (double)num);
    for (int i = 0; i < 10;)
    {
        if (eh_primo_rec(num++))
        {
            printf("%7s%.0lf\n", " ", (double)(num - 1));
            i++;
        }
    }
    while (!eh_primo_rec(num++))
        ;

    printf("Last:  %.0lf\n", (double)(--num));
}

void teste_primos()
{
    printf("%30s\n", "PRIMOS");
    printf("Testes das funcoes:\n");
    printf("busca primo com struct (busca o primo)\n");
    printf("busca primo implementacao da internet (eh_primo)\n");
    printf("busca primo recursivamente (eh_primo_rec)\n\n");

    void tp(int lim, bool (*p)(unsigned long long int))
    {
        clock_t comeco = clock();

        int c = 0;
        for (int i = 2; i < lim; i++)
        {
            c += p(i);
        }

        clock_t fim = clock();
        double tempo_gasto = (double)(fim - comeco) / CLOCKS_PER_SEC;

        printf("%10s %g\n%10s %d\n\n", "Tempo:", tempo_gasto, "Contador:", c);
    }

    int lim = 5e6;

    printf("Funcao busca o primo\n");

    clock_t t_criar_i = clock();
    PRIMOS *P = criar_primo(lim);
    clock_t t_criar_f = clock();

    clock_t comeco = clock();
    int c = 0;
    for (int i = 2; i < lim; i++)
    {
        c += eh_primo_busca(P, i);
    }
    clock_t fim = clock();

    clock_t t_destruir_i = clock();
    destruir_primo(P);
    clock_t t_destruir_f = clock();

    double tempo_gasto = (double)(fim - comeco) / CLOCKS_PER_SEC;
    double tempo_criar = (double)(t_criar_f - t_criar_i) / CLOCKS_PER_SEC;
    double tempo_destruir = (double)(t_destruir_f - t_destruir_i) / CLOCKS_PER_SEC;
    printf("Tempo para criar:    %g\n", tempo_criar);
    printf("Tempo para destruir: %g\n", tempo_destruir);
    printf("Tempo para buscar:   %g\n", tempo_gasto);
    printf("Tempo total:         %g\n", tempo_criar + tempo_destruir + tempo_gasto);
    printf("Contador:            %d\n\n", c);

    printf("Funcao eh_primo\n");
    tp(lim, eh_primo);
    printf("Funcao eh_primo_rec\n");
    tp(lim, eh_primo_rec);
}

void teste_fatores_primos()
{
    bool condicao(int x) { return x; }
    int inicio = 1, gap = 10;
    for (int i = 1; i <= 25; i++)
    {
        inicio *= i;
    }
    printf("%30s\n", "FATORES PRIMOS");
    printf("Teste entre fatores_primos iterativo e ");
    printf("fatores_primos com gerador.\n\n");
    for (int i = inicio; i < inicio + gap; i += 1)
    {
        int *p1 = fatores_primos_iter(i); // MALLOC p1
        int *p2 = fatores_primos_gen(i);  // MALLOC p2

        int n = LENGTH_PRIME_FACTORS(i);
        bool flag = false;

        if (equals_array(p1, p2, n, sizeof(int), cmpInt))
        {
            printf(" IGUAIS :: ");
        }
        else
        {
            flag = true;
            printf("DIFEREM :: ");
        }
        printf("%d = %d :: ", i, mult_array(p1, n));
        printz_array(p1, n, sizeof(int), printInt);
        if (flag)
        {
            printf("\n");
            printz_array(p1, n, sizeof(int), printInt);
        }
        printf("\n");

        free(p1); // FREE p1
        free(p2); // FREE p2
    }
}

void teste_divisores()
{
    bool condicao(int x) { return x; }
    int inicio = 1, gap = 10;
    for (int i = 1; i <= 25; i++)
    {
        inicio *= i;
    }
    printf("%d\n", inicio);
    clock_t comeco, fim;
    double tempo1, tempo2;
    printf("%30s\n", "DIVISORES");
    printf("Testa as funcoes\n");
    printf("divisores_lazy, sem optimizacao relevante, porem garante a resposta correta\n");
    printf("divisores_optm, com optimizacoes, porem nao sei se garante sempre a resposta correta\n\n");
    for (int i = inicio; i < inicio + gap; i += 1)
    {

        comeco = clock();
        int *d1 = divisores_lazy(i);
        fim = clock();
        tempo1 = (double)(fim - comeco) / CLOCKS_PER_SEC;

        comeco = clock();
        int *d2 = divisores_optm(i);
        fim = clock();
        tempo2 = (double)(fim - comeco) / CLOCKS_PER_SEC;

        int n = LENGTH_DIVIDERS(i);
        bool flag = false;

        printf("%d :: ", i);
        if (equals_array(d1, d2, n, sizeof(int), cmpInt))
        {
            printf(" IGUAIS :: ");
        }
        else
        {
            flag = true;
            printf("DIFEREM :: ");
        }
        printf("(%g, %g) :: ", tempo1, tempo2);
        printz_array(d1, n, sizeof(int), printInt);
        if (flag)
        {
            printf("\n");
            printz_array(d2, n, sizeof(int), printInt);
            printf("\n");
            system("pause");
            exit(0);
        }
        printf("\n");

        free(d1);
        free(d2);
    }
}

void teste_gerador_primos()
{
    // Ambos os geradores tem a mesma complexidade
    printf("Testa a eficiencia dos geradores\n");
    printf("gen_primos_2, com incremento 2\n");
    printf("gen_primos_w, com incremento w (6 - w) [2,4,2,4,2,4]\n");
    printf("Percebe-se que a complexidade nao muda, apesar da pequena ");
    printf("optmizacao. Sua complexidade depende da funcao que retorna ");
    printf("se e primo ou nao.\n\n");
    void tp(int lim, unsigned long long int (*p)(bool))
    {
        clock_t comeco = clock();

        unsigned long long int c = 0;
        for (int i = 0; i < lim; i++)
        {
            c += p(true);
        }

        clock_t fim = clock();
        double tempo_gasto = (double)(fim - comeco) / CLOCKS_PER_SEC;

        printf("tempo (%g) contador (%ull)\n", tempo_gasto, c);
    }
    int lim = 1e6;
    printf("Gerador 1, incremento 2 ");
    tp(lim, gen_primos_2);
    printf("Gerador 2, incremento w ");
    tp(lim, gen_primos_w);
}

int main()
{
    teste_divisores();
    system("pause");
    return 0;
}