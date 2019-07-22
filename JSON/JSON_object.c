#include "JSON_object.h"

extern inline long long int JSON_object_size_value() {
    return sizeof( dict_t );
}

// Constructor and destructor
JSON_object_t* JSON_object_new( void ) {
    return JSON_object_init( JSON_new() );
}
JSON_object_t* JSON_object_init( JSON_object_t* self ) {
    memcpy( self, &JSON_object, sizeof( JSON_object_t ) );
    self->value = Dict.New( sizeof( JSON_object_t ) );
    return self;
}
void JSON_object_del( JSON_object_t** pself ) {
    printf("(%s) Não implementado!", (*pself)->type);
}
