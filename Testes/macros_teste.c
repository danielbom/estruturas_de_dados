#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>

#define SWAP(a,b) do { typeof(a) t; t = a; a = b; b = t; } while(0)
#define CMP(a,b) a - b

#define DPRINT(fmt, ...) printf("DEBUG: "fmt"\\n", ##__VA_ARGS__)

int sum(int n, ...){
    va_list vl;
    int soma = 0;

    va_start(vl,n);

    for(int i = 0; i < n; i++)
        soma += va_arg(vl,int);
    
    va_end(vl);

    return soma;
}

int main(){
    printf("Date: %s\n", __DATE__);
    printf("File: %s\n", __FILE__);
    printf("Time: %s\n", __TIME__);
    //printf("Stdc: %s\n", __STDC__);
    //printf("Line: %s\n", __LINE__);

    printf("sizeof(void*): %d\n", sizeof(void*));
    printf("sizeof(char): %d\n", sizeof(char));
    printf("sizeof(int): %d\n", sizeof(int));
    printf("sizeof(long): %d\n", sizeof(long));
    printf("sizeof(float): %d\n", sizeof(float));
    printf("sizeof(double): %d\n", sizeof(double));
    printf("sizeof(unsigned int): %d\n", sizeof(unsigned int));
    printf("sizeof(long long): %d\n", sizeof(long long));
    printf("sizeof(long long int): %d\n", sizeof(long long int));
    printf("sizeof(long double): %d\n", sizeof(long double));

    printf("e round(e) trunc(e) %lf %lf %lf\n", M_E, round(M_E), trunc(M_E));

    int a = 5;
    int b = 10;
    printf("var_arg sum: %d\n", sum(5, 9,5,7,8,6));
    printf("SWAP: %d %d\n", a, b);
    SWAP(a, b);
    printf("SWAP: %d %d\n", a, b);
    printf("CMP: %d\n", CMP(a, b));

    printf("DPRINT: ");
    DPRINT("Valor de a = %d b = %d", a , b);
    printf("\n");

    system("pause");
    return 0;
}