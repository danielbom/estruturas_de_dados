#include <stdio.h>
#include "dict_t.h"

dict_t* d;

int cmpInt(const void* a, const void* b) {
    int *x = memcpy(malloc(sizeof(int)), a, sizeof(int));
    int *y = memcpy(malloc(sizeof(int)), b, sizeof(int));
    int cmp = *x - *y;
    free(x);
    free(y);
    return cmp;
}

void onInit() {
    printf("New\n");
    d = dict_new( sizeof(int) );
    printf("Init %p\n", (void*) d);
}

void onDelete() {
    printf("Del\n");
    d->del( &d );
}

void test_1() {
    int i, *res;
    onInit();

    i = 0;
    d->set( d, "a", &i );

    i = 100;
    d->set( d, "b", &i );

    i = 40;
    d->set( d, "z", &i );

    i = 900;
    d->set( d, "k", &i );


    res = d->get( d, "a" );
    printf("a: %d %d %p\n", 0, res ? *res : -1, (void*) res);

    res = d->get( d, "aa" );
    printf("aa: %d %d %p\n", -1, res ? *res : -1, (void*) res);

    res = d->get( d, "z" );
    printf("z: %d %d %p\n", 40, res ? *res : -1, (void*) res);

    res = d->get( d, "b" );
    printf("b: %d %d %p\n", 100, res ? *res : -1, (void*) res);

    res = d->get( d, "k" );
    printf("k: %d %d %p\n", 900, res ? *res : -1, (void*) res);

    onDelete();
}

int main() {


    test_1();


    return 0;
}
