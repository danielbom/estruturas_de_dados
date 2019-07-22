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

// Utils
void JSON_object_print( JSON_object_t* self ) {
    JSON_object_t *obj;
    dict_t* dict = self->value;
    int length = Array.length( dict->keys );
    printf("{");
    for( int i = 0; i < length; i++ ) {
        char* key = Array.get( dict->keys, i );
        printf("\"%s\": ", key);
        obj = Dict.get( dict, key );
        JSON_print( obj );
        if ( (i+1) < length ) printf(", ");
    }
    printf("}");
}