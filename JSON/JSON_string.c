#include "JSON_string.h"

extern inline long long int JSON_string_size_value() {
    return sizeof( char* );
}

// Constructor and destructor
JSON_object_t* JSON_string_new( void ) {
    return JSON_string_init( JSON_new() );
}
JSON_object_t* JSON_string_init( JSON_object_t* self ) {
    memcpy( self, &JSON_string, JSON_string_size_value() );
    self->value = calloc( 1, sizeof(char) );
    return self;
}
void JSON_string_del( JSON_object_t** pself ) {
    printf("(%s) Não implementado!", (*pself)->type);
}

// Getter and setter
void* JSON_string_get( JSON_object_t* self ) {
    return self->value;
}
void JSON_string_set( JSON_object_t* self, void* val ) {
    free( self->value );
    self->value = strdup( val );
}