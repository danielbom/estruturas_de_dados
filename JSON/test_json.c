#include "JSON.h"

int main() {
    JSON_object_t* boolean = JSON_boolean.New();
    JSON_object_t* number = JSON_number.New();
    JSON_object_t* string = JSON_string.New();
    JSON_object_t* array = JSON_array.New();
    array_t* arr = JSON_get( array );
    Array.append( arr, boolean );
    Array.append( arr, number );
    Array.append( arr, string );
    JSON_print( boolean );
    printf("\n");

    JSON_print( number );
    printf("\n");

    JSON_print( string );
    printf("\n");

    JSON_print( array );
    printf("\n");



    JSON_del( &boolean );
    JSON_del( &number );
    JSON_del( &string );
    JSON_del( &array );
    return 0;
}