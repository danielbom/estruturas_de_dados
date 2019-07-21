#ifndef JSON_INTERFACE
#define JSON_INTERFACE

#include <stdlib.h> // calloc
#include <string.h> // memcpy

typedef struct json_object_t JSON_object_t;

// type: string, array, number, object, boolean
struct json_object_t {
    char  type[10];
    void* value;

    // Constructor and destructor
    JSON_object_t* (*New) ( void );
    JSON_object_t* (*init)( JSON_object_t* self );
    JSON_object_t* (*del) ( JSON_object_t** pself );

    // Getter and setter
    void* (*get)( void );
    void  (*set)( void* );
};

JSON_object_t* JSON_new() {
    return (JSON_object_t*) calloc(1, sizeof(JSON_object_t));
}

#endif