#ifndef JSON_INTERFACE
#define JSON_INTERFACE

typedef struct json_object_t JSON_object_t;

// type: string, array, number, object, boolean
struct json_object_t {
    char type[10];
    void* value;

    // Constructor and destructor
    JSON_object_t* (*New)( void );
    JSON_object_t* (*init)();
    JSON_object_t* (*del)( JSON_object_t** pself );
};

#endif