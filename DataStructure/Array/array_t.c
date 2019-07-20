#include "array_t.h"
// --------------------------------------------- ||
//                 Private methods               ||
// --------------------------------------------- ||
#define __array_t_sift( self, pos ) ( (self)->_array + ( (self)->_size * (pos)))
void array_assertion ( array_t *self );
void array_t_open_block ( array_t* self, int pos );
void array_resize2( void** ptr_array, uint_least8_t size, int_fast16_t length );
void array_resize ( array_t *self );
// --------------------------------------------- ||
//                 Implementations               ||
// --------------------------------------------- ||
void array_assertion( array_t *self ) {
    if ( self == NULL || self->_array == NULL || self->_length == 0 || self->_size == 0 ) {
        printf("%p %p %ld %d\n", self, self->_array, self->_length, self->_size );
        printf("You need call [array]->init to configure this values.\n");
        perror("Array ERROR!!!\n" );
        exit(-1 );
    }
}
void array_t_open_block( array_t* self, int pos ) {
    int n = self->length( self );
    for ( int i = n; i > pos; i-- )
        memcpy(
            __array_t_sift( self, i ),
            __array_t_sift( self, i-1 ),
            self->_size
        );
}
void array_resize2( void** ptr_array, uint_least8_t size, int_fast16_t length ) {
    void *old_array = *ptr_array;
    int_fast16_t last_length = length;

    if ( length == INT16_MAX / 2) {
        perror("The array has reached the maximum width." );
        return;
    }

    length = length * 2 > INT16_MAX / 2 ? INT16_MAX : length * 2;
    *ptr_array = memcpy( malloc( length ), old_array, last_length * size );
    free( old_array );
}
void array_resize( array_t *self ) {
    array_assertion( self );
    array_resize2( &self->_array, self->_size, self->_length );
}
// --------------------------------------------- ||
//           Constructor and destructor          ||
// --------------------------------------------- ||
array_t* array_init( array_t *self, uint_least8_t size, int_fast16_t length ) {
    if ( self == NULL || size == 0 || length <= 0 ) {
        printf("Input: %p, %d, %ld\n", self, size, length );
        perror("Invalid argument array_init\n" );
        exit(-1 );
    }

    memcpy( self, &Array, sizeof(array_t) );
    self->_array  = calloc( length, size );
    self->_length = length;
    self->_size   = size;

    return self;
}
void array_del( array_t **pself ) {
    if ( pself == NULL ) {
        perror("Invalid argument array_insert\n" );
        exit(-1 );
    }
    array_t *self = *pself;
    array_assertion( self );

    free( self->_array );
    free( *pself );

    *pself = NULL;
}
array_t* array_new( uint_least8_t size, int_fast16_t length ) {
    return array_init( calloc(1, sizeof(array_t)), size, length );
}
// --------------------------------------------- ||
//                  Insert/Update                ||
// --------------------------------------------- ||
void array_append( array_t *self, void* val ) {
    array_assertion( self );
    if ( val == NULL ) {
        printf("Input: %p\n", val );
        perror("Invalid argument array_insert\n" );
        exit(-1 );
    }
    if ( self->_length == self->_filled ) {
        array_resize( self );
    }
    void *pos = __array_t_sift( self, self->_filled++  );
    memcpy( pos, val, self->_size  );
}
void array_set( array_t *self, void* val, int_fast16_t pos ) {
    pos = pos < 0 ? self->_filled + pos : pos;
    memcpy( array_get( self, pos ), val, self->_size );
}
void array_insert( array_t *self, void* val, int_fast16_t pos ) {
    array_assertion( self );
    if ( pos < 0 || val == NULL ) {
        printf("Input: %p, %p, %ld, %ld\n", self, val, pos, self->_filled );
        perror("Invalid argument array_insert\n" );
        exit(-1 );
    }
    if ( pos > self->_filled ) {
        pos = self->_filled;
    }
    if ( self->_length == self->_filled ) {
        array_resize( self );
    }
    if ( self->_filled == pos ) {
        self->append( self, val );
        return;
    }
    array_t_open_block( self, pos );
    memcpy( __array_t_sift( self, pos), val, self->_size );
    self->_filled++;
}
int_fast16_t array_insort( array_t *self, void* val, int (*cmp)( const void*, const void* ) ) {
    array_assertion( self );
    int_fast16_t i = 0;
    int_fast16_t n = self->length( self );
    for (i = 0; i < n; i++) {
        if ( cmp(val, __array_t_sift( self, i )) <= 0 ) {
            break;
        }
    }
    array_insert( self, val, i);
    return i;
}
// --------------------------------------------- ||
//                      Query                    ||
// --------------------------------------------- ||
void* array_get( array_t *self, int_fast16_t pos ) {
    array_assertion( self );
    if ( pos < 0 || pos > self->_filled ) {
        printf( "Input: %ld\n", pos );
        perror( "Invalid argument array_insert\n" );
        exit( -1 );
    }
    return __array_t_sift( self, pos  );
}
int_fast16_t array_bsearch( array_t *self, void* val, int (*cmp)( const void*, const void* ) ) {
    array_assertion( self );
    void* ptr = bsearch(val, self->_array, self->_filled, self->_size, cmp);
    return ptr ? (ptr - self->_array) / self->_size : -1;
}
// --------------------------------------------- ||
//                      Utils                    ||
// --------------------------------------------- ||
int_fast16_t array_length( array_t *self ) {
    return self->_filled;
}
void array_fatten ( array_t *self ) {
    self->_filled = self->_length;
}