CC=gcc
CXX=g++

all: testes

testes:
	${CC} BST_teste.c -o bst.exe
	${CC} AVLT_teste.c -o avlt.exe
	${CC} RBT_teste.c -o rbt.exe

clean: 
	rm *.exe

info:
	@echo "For compiling with DEBUG messages, use:"
	@echo "make OPTIONS=\"-DVERBOSE -DDEBUG\""