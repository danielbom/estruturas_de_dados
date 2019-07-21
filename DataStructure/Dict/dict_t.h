#ifndef DICT_T
#define DICT_T

#include "../Array/array_t.h"
#include <stdlib.h>
#include <string.h>

typedef struct dict_t dict_t;

// --------------------------------------------- ||
//                   Definitions                 ||
// --------------------------------------------- ||

struct dict_t {
    array_t* keys;
    array_t* values;

    // Constructor and destructor
    dict_t* (*New) ( uint_least8_t size );
    dict_t* (*init)( dict_t* self, uint_least8_t size );
    void    (*del) ( dict_t** pself );

    // Insert/Update
    dict_t* (*set)( dict_t*, char* , void* );

    // Query
    void*   (*get)( dict_t*, char* );
};

// Constructor and destructor
dict_t* dict_new ( uint_least8_t size );
dict_t* dict_init( dict_t* self, uint_least8_t size );
void    dict_del ( dict_t** pself );

// Insert/Update
dict_t* dict_set( dict_t* self, char* key, void* val );

// Query
void*   dict_get( dict_t* self, char* key );

static const dict_t Dict = {
    0, 0,
    &dict_new,
    &dict_init,
    &dict_del,

    &dict_set,
    &dict_get
};

#endif