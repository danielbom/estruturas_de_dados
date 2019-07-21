#include "JSON_boolean.h"

inline long long int JSON_boolean_size_value() {
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
void JSON_boolean_del( JSON_object_t** pself ) {
    printf("(BOOL) Não implementado!");
}


// Getter and setter
void* JSON_boolean_get( JSON_object_t* self ) {
    return self->value;
}
void JSON_boolean_set( JSON_object_t* self, void* val ) {
    memcpy( self->value, val, JSON_boolean_size_value() );
}