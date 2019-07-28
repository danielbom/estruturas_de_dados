#include "../JSON_number.h"

extern inline long long int JSON_number_size_value() {
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

// Utils
void JSON_number_print( JSON_object_t* self ) {
    printf( "%lld", *(long long int*) self->get( self ) );
}