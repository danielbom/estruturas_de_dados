#ifndef JSON_STRING
#define JSON_STRING

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* JSON_string_new( void );
JSON_object_t* JSON_string_init( JSON_object_t* self );

// Getter and setter
void  JSON_string_set( JSON_object_t* self, void* val );

// Utils
void JSON_string_print( JSON_object_t* self );

static const JSON_object_t JSON_string = {
    "String", 0,
    &JSON_string_new,
    &JSON_string_init,
    &JSON_default_del,
    &JSON_default_get,
    &JSON_string_set,
    &JSON_string_print
};

#endif