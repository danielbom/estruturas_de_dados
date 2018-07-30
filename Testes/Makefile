CC=gcc
CXX=g++

all: testes

testes:
	${CC} Lista_teste.c -o lista.exe
	${CC} Fila_teste.c -o fila.exe
	${CC} BST_teste.c -o bst.exe
	${CC} Pilha_teste.c -o pilha.exe
	${CC} primo_teste.c -o primos.exe
	${CC} macros_teste.c -o macros.exe

clean: 
	rm *.exe

info:
	@echo "For compiling with DEBUG messages, use:"
	@echo "make OPTIONS=\"-DVERBOSE -DDEBUG\""