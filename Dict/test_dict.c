#include <stdio.h>
#include "dict_t.h"

dict_t* d;

int cmpInt(const void* a, const void* b) {
    int x = *(int*) a;
    int y = *(int*) b;
    int cmp = x - y;
    return cmp;
}

void onInit() {
    printf("New\n");
    d = dict_new( sizeof(int) );
    printf("Init %p\n", d);
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
    printf("a: %d %d %p\n", 0, res ? *res : -1, res);

    res = d->get( d, "aa" );
    printf("aa: %d %d %p\n", -1, res ? *res : -1, res);

    res = d->get( d, "z" );
    printf("z: %d %d %p\n", 40, res ? *res : -1, res);

    res = d->get( d, "b" );
    printf("b: %d %d %p\n", 100, res ? *res : -1, res);

    res = d->get( d, "k" );
    printf("k: %d %d %p\n", 900, res ? *res : -1, res);

    onDelete();
}

int main(int argc, char const *argv[]) {

    
    test_1();


    return 0;
}
