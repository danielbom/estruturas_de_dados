gcc -c test_dict.c array_t.c dict_t.c
gcc -o $1 test_dict.o array_t.o dict_t.o
rm *.o