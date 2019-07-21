#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "array_t.h"

array_t* a;

int cmpInt(const void* a, const void* b) {
    int *x = (int*) a;
    int *y = (int*) b;
    int cmp = *x - *y;
    return cmp;
}

void onInit() {
    printf("New\n");
    a = Array.New( sizeof(int), 4 );
    printf("Init %p\n", (void*) a);
}

void print() {
    int n = Array.length(a);
    printf("Print %d\n", n);
    for (int i = 0; i < n; i++) {
        int *p = Array.get(a, i);
        printf("%d %d %p\n", i, *p, (void*) p);
    }
    printf("\n");
}

void append() {
    printf("Append\n");
    for (int i = 0; i < 8; i++) {
        int j = i * 10;
        Array.append(a, &j);
    }
}

void onDelete() {
    printf("Del\n");
    Array.del( &a );
}

void test_1() {
    printf("Teste 1: Append, insert, get\n");
    onInit();
    append();

    printf("Insert\n");
    int i = 111;
    Array.insert(a, &i, 0);
    i = 999;
    Array.insert(a, &i, 7);
    i = 99;
    Array.insert(a, &i, 5);

    printf("\n");

    print();
    onDelete();
}

void test_2() {
    printf("Teste 2: Insort, bsearch\n");
    onInit();
    printf("\n");
    append();
    printf("\n");

    printf("Insort\n");
    int i = 45;
    printf("Inserted at: %ld\n", Array.insort(a, &i, &cmpInt));
    i = 90;
    printf("Inserted at: %ld\n", Array.insort(a, &i, &cmpInt));
    i = 60;
    printf("Inserted at: %ld\n", Array.insort(a, &i, &cmpInt));
    printf("\n");
    print();

    printf("Bsearch\n");
    i = 45;
    printf("Search %d %ld\n", i, Array.bsearch(a, &i, &cmpInt));
    i = 46;
    printf("Search %d %ld\n", i, Array.bsearch(a, &i, &cmpInt));
    i = 90;
    printf("Search %d %ld", i, Array.bsearch(a, &i, &cmpInt));
    printf("\n");

    onDelete();
    printf("\n");
}

void test_3() {
    onInit();
    append();
    print();
    for(int i = 0; i < Array.length(a); i++) {
        Array.set(a, &i, i);
    }
    print();
    onDelete();
}

void test_4() {
    onInit();
    Array.fatten(a);
    print();
    onDelete();
}

int main() {
    test_2();
    return 0;
}