#include "JSON_array.h"

extern inline long long int JSON_array_size_value() {
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
    JSON_object_t* self = *pself;
    array_t* value = JSON_get( self );
    Array.del( &value );
    free( self );
    *pself = NULL;
}


// Getter and setter
void* JSON_array_get( JSON_object_t* self ) {
    return self->value;
}
void  JSON_array_set( JSON_object_t* self, void* val ) {
    memcpy( self->value, val, JSON_array_size_value() );
}

// Utils
void JSON_array_print( JSON_object_t* self ) {
    JSON_object_t* obj;
    array_t *array = (array_t*) self->get( self );
    int length = Array.length( array );
    printf("[");
    for ( int i = 0; i < length; i++ ) {
        obj = Array.get( array, i );
        JSON_print( obj );
        if ( (i+1) < length ) printf(", ");
    }
    printf("]");
}
