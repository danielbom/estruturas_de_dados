#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* IMPRESSAO DE TIPOS PRIMARIOS */
void printInt(void* v){
    printf("%d ", *(int*)v);
}
void printFloat(void* v){
    printf("%f ", *(float*)v);
}
void printDouble(void* v){
    printf("%lf ", *(double*)v);
}
void printChar(void* v){
    printf("%c ", *(char*)v);
}
void printString(void* v){
    printf("%s ", *(char**)v);
}

/* COMPARACAO DE TIPOS PRIMARIOS */
int compararInt(void* a, void* b){
    return *(int*)a > *(int*)b ? 1 : (*(int*)a < *(int*)b ? -1 : 0);
}
int compararFloat(void* a, void* b){
    return *(float*)a > *(float*)b ? 1 : (*(float*)a < *(float*)b ? -1 : 0);
}
int compararDouble(void* a, void* b){
    return *(double*)a > *(double*)b ? 1 : (*(double*)a < *(double*)b ? -1 : 0);
}
int compararChar(void* a, void* b){
    return *(char*)a > *(char*)b ? 1 : (*(char*)a < *(char*)b ? -1 : 0);
}
int compararString(void* a, void* b){
    return strcmp(*(char**)a, *(char**)b);
}