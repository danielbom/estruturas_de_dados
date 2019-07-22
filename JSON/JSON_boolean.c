#include "JSON_boolean.h"

extern inline long long int JSON_boolean_size_value() {
    return sizeof( char );
}

// Constructor and destructor
JSON_object_t* JSON_boolean_new( void ) {
    return JSON_boolean_init( JSON_new() );
}
JSON_object_t* JSON_boolean_init( JSON_object_t* self ) {
    memcpy( self, &JSON_boolean, sizeof( JSON_object_t ) );
    self->value = calloc( 1, JSON_boolean_size_value() );
    return self;
}

// Utils
void JSON_boolean_print( JSON_object_t* self ) {
    char boolean = *(char*) self->get( self );
    if (boolean) {
        printf("true");
    } else {
        printf("false");
    }
}