#include "JSON_number.h"

inline long long int JSON_number_size_value() {
    return sizeof( long long int );
}

// Constructor and destructor
JSON_object_t* JSON_number_new( void ) {
    return JSON_number_init( JSON_new() );
}
JSON_object_t* JSON_number_init( JSON_object_t* self ) {
    memcpy( self, &JSON_number, sizeof( JSON_object_t ) );
    self->value = calloc(1, JSON_number_size_value() );
    return self;
}
void JSON_number_del( JSON_object_t** pself ) {
    printf("(NUMBER) Não implementado!");
}

// Getter and setter
void* JSON_number_get( JSON_object_t* self ) {
    return self->value;
}
void  JSON_number_set( JSON_object_t* self, void* val ) {
    memcpy( self->value, val, JSON_number_size_value()  );
}