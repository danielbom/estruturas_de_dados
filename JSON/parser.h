#ifndef JSON_PARSER
#define JSON_PARSER

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct parser_t parser_t;

struct parser_t {
    FILE* source_code;
    char ch;
    int line, col;

    // Constructor and destructor
    parser_t* (*New) ( void );
    parser_t* (*init)( parser_t* self, char* filename );
    void (*del) ( parser_t** pself );

    // Utils
    parser_t* (*parse)( parser_t* self );
};

// Definitions
parser_t* parser_new();
parser_t* parser_init( parser_t* self, char* filename );
void parser_del( parser_t** pself );
parser_t* parser_parse( parser_t* self );

static const parser_t Parser = {
    0, 0, 0, 0,
    &parser_new,
    &parser_init,
    &parser_del,
    &parser_parse
};

#endif