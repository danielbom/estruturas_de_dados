#include "../parser.h"


parser_t* parser_new() {
    return (parser_t*) calloc(1, sizeof( parser_t ) );
}
parser_t* parser_init( parser_t* self, char* filename ) {
    memcpy( self, &Parser, sizeof( parser_t ) );
    self->source_code = fopen( filename, "r" );
    return self;
};
void parser_del( parser_t** pself ) {
    parser_t* self = *pself;
    if ( self->source_code )
        fclose( self->source_code );
    free( self );
    *pself = NULL;
}

// Utils
void parser_next( parser_t* self ) {
    self->ch = fgetc( self->source_code );
}
parser_t* parser_parse( parser_t* self ) {
    if ( self->source_code ) {
        FILE* f = self->source_code;
        fseek( f, 0, SEEK_SET );

        self->line = 0;
        self->col = 0;
        printf( "\n\n---> BEGIN OF PARSE\n\n");
        for ( char ch = fgetc( f ); ch != EOF; ch = fgetc( f ) ) {
            switch(ch) {
                case '\n':
                    self->line++;
                    self->col = 0;
                    break;
                case '{':
                    break;
                case '}':
                    break;
                case '[':
                    break;
                case ']':
                    break;
                case '"':
                    break;
                case ' ':
                    break;
                default:
                    break;
            }

            printf( "%c", ch );

        }
        printf( "\n\n---> END OF PARSE\n\n" );

    }
    return self;
}