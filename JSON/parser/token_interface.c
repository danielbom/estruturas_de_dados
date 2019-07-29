#ifndef TOKEN_INTERFACE
#define TOKEN_INTERFACE

#include "parser.h"

typedef struct token_t token_t;

struct token_t {
    parser_t* parser;
    char name[64];

    // Constructor and destructor
    token_t* (*New)( void );
    token_t* (*init)( token_t* self, parser_t* parser );
    void (*del)( token_t** pself );

    // Utils
    void (*print)( token_t* self );
    void (*parse)( token_t* self );
};

token_t* token_new() {
    return (token_t*) calloc( 1, sizeof( token_t ) );
}

void token_print( token_t* self ) {
    self->print( self );
}

void Token_parse( token_t* self ) {
    self->parse( self );
}

#endif