
LIB="parser/parser.c"
OBJ="parser.o"

gcc -c test_parser_json.c $LIB
gcc -o $1 test_parser_json.o $OBJ
gcc -g test_parser_json.c $LIB -o debug
mv *.o obj/