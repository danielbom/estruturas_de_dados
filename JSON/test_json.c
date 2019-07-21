#include "JSON.h"

int main() {
    JSON_object_t* boolean = JSON_boolean.New();
    JSON_object_t* number = JSON_number.New();
    JSON_object_t* string = JSON_string.New();
    JSON_print( boolean );
    printf("\n");
    JSON_print( number );
    printf("\n");
    JSON_print( string );

    JSON_del( &boolean );
    printf("\n");
    JSON_del( &number );
    printf("\n");
    JSON_del( &string );
    printf("\n");
    return 0;
}