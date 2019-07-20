gcc -c test_array.c array_t.c
gcc -o $1 test_array.o array_t.o
gcc -g test_array.c array_t.c -o debug
rm *.o