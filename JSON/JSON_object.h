#ifndef OBJECT_JSON
#define OBJECT_JSON

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* JSON_object_new( void );
JSON_object_t* JSON_object_init( JSON_object_t* self );
void JSON_object_del( JSON_object_t** pself );

static const JSON_object_t JSON_object = {
    "Object", 0,
    &JSON_object_new,
    &JSON_object_init,
    &JSON_object_del
};

#endif