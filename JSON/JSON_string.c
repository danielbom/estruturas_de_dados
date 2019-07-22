#include "JSON_string.h"

extern inline long long int JSON_string_size_value() {
    return sizeof( char* );
}

// Constructor and destructor
JSON_object_t* JSON_string_new( void ) {
    return JSON_string_init( JSON_new() );
}
JSON_object_t* JSON_string_init( JSON_object_t* self ) {
    memcpy( self, &JSON_string, sizeof( JSON_object_t ) );
    self->value = calloc( 1, sizeof(char) );
    return self;
}

// Utils
void JSON_string_print( JSON_object_t* self ) {
    printf("\"%s\"", (char*) self->get( self ));
}
