CC=gcc
CXX=g++

all: testes

testes:
	${CC} array_teste.c -o array.exe
	${CC} macros_teste.c -o macros.exe
	${CC} primo_teste.c -o primo.exe -lm
	
clean: 
	rm *.exe

info:
	@echo "For compiling with DEBUG messages, use:"
	@echo "make OPTIONS=\"-DVERBOSE -DDEBUG\""