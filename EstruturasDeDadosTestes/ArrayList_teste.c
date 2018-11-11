#include "../EstruturasDeDados/ArrayList2.h"

int main()
{
    ArrayList* array = random_int_ArrayList(0, 50, 20);

    println_ArrayList(array, printInt);

    clear_ArrayList(array);

    clock_t comeco = clock();
    println_ArrayList(array, printInt);
    resize_ArrayList(array, 10000);
    
    for(int i = 0; i < 10000; i++)
        push_back_ArrayList(array, &i);
    clock_t fim = clock();
    
    double tempo_gasto = (double)(fim - comeco) / CLOCKS_PER_SEC;

    //println_ArrayList(array, printInt);
    printf("Tempo: %g\n\n", tempo_gasto);

    delete_ArrayList(&array);
    return 0;
}