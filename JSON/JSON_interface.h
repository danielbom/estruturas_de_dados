#ifndef JSON_INTERFACE
#define JSON_INTERFACE

#include <stdlib.h> // calloc
#include <string.h> // memcpy
#include <stdio.h>  // printf

typedef struct json_object_t JSON_object_t;

// type: string, array, number, object, boolean
struct json_object_t {
    char  type[10];
    void* value;

    // Constructor and destructor
    JSON_object_t* (*New) ( void );
    JSON_object_t* (*init)( JSON_object_t* self );
    void (*del) ( JSON_object_t** pself );

    // Getter and setter
    void* (*get)( JSON_object_t* self );
    void  (*set)( JSON_object_t* self, void* val );
};

static JSON_object_t* JSON_new() {
    return (JSON_object_t*) calloc(1, sizeof(JSON_object_t));
}

#endif