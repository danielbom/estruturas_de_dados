#ifndef DICT_T
#define DICT_T

#include "array_t.h"
#include <stdlib.h>
#include <string.h>

typedef struct dict_t dict_t;

// --------------------------------------------- ||
//                   Definitions                 ||
// --------------------------------------------- ||

struct dict_t {
    array_t* _keys;
    array_t* _values;

    dict_t* (*new)  ( uint_least8_t size );
    dict_t* (*init)( dict_t*, uint_least8_t );
    dict_t* (*set) ( dict_t*, char* , void* );
    void* (*get)( dict_t*, char* );
    void (*del) ( dict_t** );
};

dict_t* dict_new( uint_least8_t size );
dict_t* dict_init( dict_t* self, uint_least8_t size );
dict_t* dict_set( dict_t* self, char* key, void* val );
void* dict_get( dict_t* self, char* key );
void dict_del( dict_t** pself );

const static dict_t Dict = {
    0, 0,
    &dict_new,
    &dict_init,
    &dict_set,
    &dict_get,
    &dict_del
};

#endif