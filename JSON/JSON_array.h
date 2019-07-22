#ifndef JSON_ARRAY
#define JSON_ARRAY

#include "JSON_interface.h"
#include "../DataStructure/Array/array_t.h"

// Constructor and destructor
JSON_object_t* JSON_array_new( void );
JSON_object_t* JSON_array_init( JSON_object_t* self );

// Getter and setter
void  JSON_array_set( JSON_object_t* self, void* val );

// Utils
void JSON_array_print( JSON_object_t* self );

static const JSON_object_t JSON_array = {
    "Array", 0,
    &JSON_array_new,
    &JSON_array_init,
    &JSON_default_del,
    &JSON_default_get,
    &JSON_array_set,
    &JSON_array_print
};


#endif