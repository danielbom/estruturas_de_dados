#include "parser.h"

int main() {
    parser_t* parser = Parser.New();
    Parser.init( parser, "Examples/1.json" );
    Parser.parse( parser );
    Parser.del( &parser );

    return 0;
}