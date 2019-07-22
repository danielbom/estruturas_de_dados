#ifndef JSON_BOOLEAN
#define JSON_BOOLEAN

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* JSON_boolean_new( void );
JSON_object_t* JSON_boolean_init( JSON_object_t* self );

// Getter and setter
void  JSON_boolean_set( JSON_object_t* self, void* val );

// Utils
void JSON_boolean_print( JSON_object_t* self );

static const JSON_object_t JSON_boolean = {
    "Boolean", 0,
    &JSON_boolean_new,
    &JSON_boolean_init,
    &JSON_default_del,
    &JSON_default_get,
    &JSON_boolean_set,
    &JSON_boolean_print
};


#endif