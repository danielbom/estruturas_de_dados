
JSON_LIB="JSON_array.c JSON_object.c JSON_string.c JSON_number.c JSON_boolean.c"
JSON_OBJ="JSON_array.o JSON_object.o JSON_string.o JSON_number.o JSON_boolean.o"

DEP_LIB="../DataStructure/Array/array_t.c ../DataStructure/Dict/dict_t.c"
DEP_OBJ="array_t.o dict_t.o"

gcc -c test_json.c $JSON_LIB $DEP_LIB
gcc -o $1 test_json.o $JSON_OBJ $DEP_OBJ
gcc -g test_json.c $JSON_LIB $DEP_LIB -o debug
rm *.o