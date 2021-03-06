# DEP: dependences
DEP=../Array/array_t.c
DEP_OBJ=array_t.o

# FLAGS="-Wextra -Wall -Werror -Wshadow -Wpointer-arith -Wcast-align -Wcast-qual -Wconversion -Wunreachable-code -Winit-self -pedantic -save-temps -S -masm=intel -fverbose-asm"
FLAGS="-Wextra -Wall -Wshadow "

# Compiling
gcc $FLAGS -c test_dict.c dict_t.c $DEP
gcc -o $1 test_dict.o dict_t.o $DEP_OBJ
gcc -g test_dict.c dict_t.c $DEP_OBJ -o debug
rm *.o