#ifndef OBJECT_JSON
#define OBJECT_JSON

#include "JSON_interface.h"
#include "../DataStructure/Dict/dict_t.h"

// Constructor and destructor
JSON_object_t* JSON_object_new( void );
JSON_object_t* JSON_object_init( JSON_object_t* self );
void JSON_object_del( JSON_object_t** pself );

// Utils
void JSON_object_print( JSON_object_t* self );

static const JSON_object_t JSON_object = {
    "Object",
    sizeof(dict_t*),
    0,
    &JSON_object_new,
    &JSON_object_init,
    &JSON_object_del,
    &JSON_default_get,
    &JSON_default_set,
    &JSON_object_print
};

#endif