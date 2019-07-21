#ifndef JSON_BOOLEAN
#define JSON_BOOLEAN

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* (JSON_boolean_new)( void );
JSON_object_t* (JSON_boolean_init)( JSON_object_t* self );
JSON_object_t* (JSON_boolean_del)( JSON_object_t** pself );

static const JSON_object_t JSON_boolean = {
    "Object", 0,
    &JSON_boolean_new,
    &JSON_boolean_init,
    &JSON_boolean_del
};


#endif