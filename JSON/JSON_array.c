#include "JSON_array.h"

inline long long int JSON_array_size_value() {
    return sizeof( array_t );
}

// Constructor and destructor
JSON_object_t* JSON_array_new( void ) {
    return JSON_array_init( JSON_new() );
}
JSON_object_t* JSON_array_init( JSON_object_t* self ) {
    memcpy( self, &JSON_array, sizeof( JSON_object_t ) );
    self->value = Array.New( sizeof(JSON_object_t), 4 );
    return self;
}
void JSON_array_del( JSON_object_t** pself ) {
    printf("(ARRAY) Não implementado!");
}


// Getter and setter
void* JSON_array_get( JSON_object_t* self ) {
    return self->value;
}
void  JSON_array_set( JSON_object_t* self, void* val ) {
    memcpy( self->value, val, JSON_array_size_value() );
}