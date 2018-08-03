CC=gcc
CXX=g++

all: testes

testes:
	${CC} primo_teste.c -o primos.exe
	${CC} macros_teste.c -o macros.exe
	${CC} primo_teste.c -o primo.exe
	
clean: 
	rm *.exe

info:
	@echo "For compiling with DEBUG messages, use:"
	@echo "make OPTIONS=\"-DVERBOSE -DDEBUG\""