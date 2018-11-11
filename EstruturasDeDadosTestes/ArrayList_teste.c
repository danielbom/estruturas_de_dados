#include "../EstruturasDeDados/ArrayList2.h"

int main()
{
    int zero = 0;
    ArrayList* array = random_int_ArrayList(0, 50, 10);
    push_back_ArrayList(array, &zero);
    push_front_ArrayList(array, &zero);
    printf("Initial random array with 0 in front and back.\n");
    println_ArrayList(array, printInt);

    resize_ArrayList(array, array->length + 20);

    for(int i = 0; i < 10; i++)
        push_back_ArrayList(array, &i);
    
    printf("0 a 9 pushing back.\n");
    println_ArrayList(array, printInt);

    for(int i = 0; i < 10; i++)
        push_front_ArrayList(array, &i);

    printf("0 a 9 pushing front.\n");        
    println_ArrayList(array, printInt);

    for(int i = 0; i < 5; i++)
        pop_back_ArrayList(array);
    
    printf("5 numbers removed to back.\n");
    println_ArrayList(array, printInt);

    for(int i = 0; i < 5; i++)
        pop_front_ArrayList(array);

    printf("5 numbers removed to front.\n");
    println_ArrayList(array, printInt);

    insert_ArrayList(array, &zero, 10);

    printf("Inserting a 0 value in position 10.\n");
    println_ArrayList(array, printInt);

    int _999 = 999;
    set_in_ArrayList(array, &_999, 10);

    printf("Changing position 10 with to value 999.\n");
    println_ArrayList(array, printInt);

    sort_ArrayList(array, cmpInt);

    printf("Sorting the list.\n");
    println_ArrayList(array, printInt);

    unique_ArrayList(array, cmpInt);

    printf("Unique the list.\n");
    println_ArrayList(array, printInt);

    reverse_ArrayList(array);

    printf("Reverse the list.\n");
    println_ArrayList(array, printInt);

    clear_ArrayList(array);
    /*
    clock_t comeco = clock();
    println_ArrayList(array, printInt);
    resize_ArrayList(array, 10000);
    
    for(int i = 0; i < 10000; i++)
        push_back_ArrayList(array, &i);
    clock_t fim = clock();
    
    double tempo_gasto = (double)(fim - comeco) / CLOCKS_PER_SEC;

    //println_ArrayList(array, printInt);
    printf("Tempo: %g\n\n", tempo_gasto);
    */
    delete_ArrayList(&array);
    return 0;
}