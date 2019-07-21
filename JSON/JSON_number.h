#ifndef JSON_NUMBER
#define JSON_NUMBER

#include "JSON_interface.h"

// Constructor and destructor
JSON_object_t* (JSON_number_new)( void );
JSON_object_t* (JSON_number_init)();
JSON_object_t* (JSON_number_del)( JSON_object_t** pself );

static const JSON_object_t JSON_object = {
    "Object", 0,
    &JSON_number_new,
    &JSON_number_init,
    &JSON_number_del
};


#endif