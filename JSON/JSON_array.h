#ifndef JSON_ARRAY
#define JSON_ARRAY

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* JSON_array_new( void );
JSON_object_t* JSON_array_init( JSON_object_t* self );
void JSON_array_del( JSON_object_t** pself );

static const JSON_object_t JSON_array = {
    "Object", 0,
    &JSON_array_new,
    &JSON_array_init,
    &JSON_array_del
};


#endif