#include "dict_t.h"

// --------------------------------------------- ||
//                 Implementations               ||
// --------------------------------------------- ||

void dict_assertion( dict_t* self ) {
    if ( self == NULL || self->keys == NULL || self->values == NULL ) {
        printf("%p %p %p\n", self, self->keys, self->values );
        printf("You need call [dict]->init to configure this values.\n");
        perror("dict ERROR!!!\n" );
        exit( -1 );
    }
}

int dict_key_cmp( const void* a, const void* b ) {
    return strcmp( a, b );
}

void* dict_get( dict_t* self, char* key ) {
    dict_assertion( self );
    array_t* k = self->keys;
    array_t* v = self->values;

    int pos = k->bsearch( k, key, dict_key_cmp );

    if ( pos == -1 ) return NULL;

    return v->get(v, pos);
}

dict_t* dict_set( dict_t* self, char* key, void* val ) {
    dict_assertion( self );

    array_t* k = self->keys;
    array_t* v = self->values;

    int pos = k->bsearch( k, key, dict_key_cmp );
    if ( pos == -1 ) {
        pos = k->insort( k, strdup(key), dict_key_cmp );
        v->insert( v, val, pos );
    } else {
        v->set( v, val, pos );
    }

    return self;
}

dict_t* dict_init( dict_t* self, uint_least8_t size ) {
    memcpy( self, &Dict, sizeof(dict_t) );

    self->keys   = array_new( sizeof(char*), 64 );
    self->values = array_new( size, 64 );
    return self;
}

void dict_del( dict_t** pself ) {
    dict_t* self = *pself;
    dict_assertion( self );

    array_t* k = self->keys;
    k->del( &k );

    array_t* v = self->values;
    v->del( &v );

    free( *pself );
    *pself = NULL;
}

dict_t* dict_new( uint_least8_t size ) {
    return dict_init( calloc(1, sizeof(dict_t)), size );
}