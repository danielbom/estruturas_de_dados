#ifndef JSON_STRING
#define JSON_STRING

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* JSON_string_new( void );
JSON_object_t* JSON_string_init( JSON_object_t* self );
void JSON_string_del( JSON_object_t** pself );

static const JSON_object_t JSON_string = {
    "String", 0,
    &JSON_string_new,
    &JSON_string_init,
    &JSON_string_del
};


#endif