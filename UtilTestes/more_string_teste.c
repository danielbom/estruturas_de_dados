#include "../Util/tipos_primarios.h"
#include "../Util/more_strings.h"

void replace_teste()
{
    char frase[] = "por{} voce {}ria saber {} dia {} eu vou embora?";

    char *resultado = replace_string(frase, "{}", "que"); // MALLOC resultado

    printf("%s\n", frase);
    printf("%s\n", resultado);

    free(resultado);
}

void split_teste()
{
    char frase[] = "porque voce queria saber que dia que eu vou embora?";
    int qtde, i;
    char **split = split_string(frase, " ", &qtde);
    printf("%s\n", frase);
    printf("%d\n", qtde);

    printf("( ");
    for (i = 0; i < qtde; i++)
        printf("%s, ", split[i]);
    printf(")");

    for (i = 0; i < qtde; i++)
        free(split[i]);
    free(split);
}

int main()
{
    split_teste();
    return 0;
}