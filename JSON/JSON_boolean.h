#ifndef JSON_BOOLEAN
#define JSON_BOOLEAN

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* (JSON_boolean_new)( void );
JSON_object_t* (JSON_boolean_init)( JSON_object_t* self );
JSON_object_t* (JSON_boolean_del)( JSON_object_t** pself );

// Getter and setter
void* JSON_boolean_get( JSON_object_t* );
void  JSON_boolean_set( JSON_object_t*, void* val );

static const JSON_object_t JSON_boolean = {
    "Object", 0,
    &JSON_boolean_new,
    &JSON_boolean_init,
    &JSON_boolean_del,
    &JSON_boolean_get,
    &JSON_boolean_set
};


#endif