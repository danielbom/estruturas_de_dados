#ifndef JSON_NUMBER
#define JSON_NUMBER

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* JSON_number_new( void );
JSON_object_t* JSON_number_init( JSON_object_t* self );

// Getter and setter
void  JSON_number_set( JSON_object_t* self, void* val );

// Utils
void JSON_number_print( JSON_object_t* self );

static const JSON_object_t JSON_number = {
    "Number", 0,
    &JSON_number_new,
    &JSON_number_init,
    &JSON_default_del,
    &JSON_default_get,
    &JSON_number_set,
    &JSON_number_print
};


#endif