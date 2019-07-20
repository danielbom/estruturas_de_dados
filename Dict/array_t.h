#ifndef ARRAY_T
#define ARRAY_T

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// --------------------------------------------- ||
//                   Definitions                 ||
// --------------------------------------------- ||
typedef struct array_t array_t;

struct array_t {
    uint_least8_t _size;
    int_fast16_t _length;
    int_fast16_t _filled;
    void* _array;

    // Constructor and destructor
    array_t* (*new) ( uint_least8_t size, int_fast16_t length );
    array_t* (*init)  ( array_t* self, uint_least8_t size, int_fast16_t length );
    void  (*del)   ( array_t** self );
    // Insert/Update
    void  (*append)( array_t* self, void* val );
    void  (*set)   ( array_t* self, void* val, int_fast16_t pos);
    void (*insert)( array_t* self, void* val, int_fast16_t pos );
    int_fast16_t (*insort) ( array_t* self, void* val, int (*cmp)( const void*, const void* ) );
    // Query
    void* (*get)   ( array_t* self, int_fast16_t pos );
    int_fast16_t (*bsearch)( array_t* self, void* val, int (*cmp)( const void*, const void* ) );
    // Utils
    void (*fatten)( array_t* self );
    int_fast16_t (*length)( array_t* self);
};

array_t* array_new ( uint_least8_t size, int_fast16_t length );
array_t* array_init( array_t *self, uint_least8_t size, int_fast16_t length );

void array_del   ( array_t **self );
void array_append( array_t *self, void* val );
void* array_get  ( array_t *self, int_fast16_t pos );
void array_set   ( array_t *self, void* val, int_fast16_t pos );

void array_insert ( array_t *self, void* val, int_fast16_t pos );
void array_fatten ( array_t *self );

int_fast16_t array_insort ( array_t *self, void* val, int (*cmp)( const void*, const void* ) );
int_fast16_t array_bsearch( array_t *self, void* val, int (*cmp)( const void*, const void* ) );

int_fast16_t array_length ( array_t *self );

// Singleton operation
const static array_t Array = {
    0, 0, 0, 0,
    &array_new,
    &array_init,
    &array_del,
    &array_append,
    &array_set,
    &array_insert,
    &array_insort,
    &array_get,
    &array_bsearch,
    &array_fatten,
    &array_length
};

#endif