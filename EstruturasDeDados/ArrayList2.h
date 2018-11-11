#ifndef ARRAY_LIST
#define ARRAY_LIST

#include "../Util/tipos_primarios.h"
#include "../Util/array.h"

typedef struct arraylist
{
    void *array;
    int quantity;
    int length;
    size_t size;

    int (*cmp)(const void*, const void*);
    int (*print)(const void*);
} ArrayList;

/* CONSTRUTOR E DESTRUTOR */
ArrayList* new_ArrayList(size_t size, int length);  // 10/11/2018
void delete_ArrayList(ArrayList **self);            // 10/11/2018

void delete_with_ArrayList(ArrayList **self, void (*delete)(const void*)); // TODO

/* FUNCOES DE INSERCAO */
bool push_back_ArrayList(ArrayList *self, void *elem);  // 10/11/2018
bool push_front_ArrayList(ArrayList *self, void *elem); // 10/11/2018

/* FUNCOES DE REMOCAO */
bool pop_back_ArrayList(ArrayList *self);        // 10/11/2018
bool pop_front_ArrayList(ArrayList *self);       // 10/11/2018
void *pop_back_data_ArrayList(ArrayList *self);  // 10/11/2018
void *pop_front_data_ArrayList(ArrayList *self); // 10/11/2018

/* FUNCOES AUXILIARES */
void resize_ArrayList(ArrayList *self, int length); // 10/11/2018
void shrink_ArrayList(ArrayList *self);             // 10/11/2018

void shift_ArrayList(ArrayList *self, int n_shift); // 10/11/2018
ArrayList* dup_ArrayList(ArrayList *self);          // 10/11/2018

bool empty_ArrayList(ArrayList *self); // 10/11/2018
bool full_ArrayList(ArrayList *self);  // 10/11/2018

void* begin_ArrayList(ArrayList *self); // 10/11/2018
void* end_ArrayList(ArrayList *self);   // 10/11/2018

ArrayList* random_int_ArrayList(int begin, int end, int length); // 10/11/2018

void* clear_ArrayList(ArrayList *self);

void print_ArrayList(ArrayList *self, void (*print)(const void*));
void println_ArrayList(ArrayList *self, void (*print)(const void*));
void print_if_ArrayList(ArrayList *self, void (*print)(const void*), int (*condition)(const void*));

/* CONSTRUTOR E DESTRUTOR */
ArrayList *new_ArrayList(size_t size, int length)
{
    if(length <= 0) return NULL;
    if(size <= 0) return NULL;

    ArrayList* new = (ArrayList*) malloc(sizeof(ArrayList));

    new->array    = calloc(length, size);
    new->length   = length;
    new->size     = size;
    new->quantity = 0;

    return new;
}
void delete_ArrayList(ArrayList **self)
{
    free((*self)->array);
    free(*self);
}

/* FUNCOES DE INSERCAO */
bool push_back_ArrayList(ArrayList *self, void *elem)
{
    if(full_ArrayList(self))
        resize_ArrayList(self, self->length + 1);
    
    memcpy(end_ArrayList(self) + self->size, elem, self->size);
    self->quantity++;
}
bool push_front_ArrayList(ArrayList *self, void *elem)
{
    if(full_ArrayList(self))
        shift_ArrayList(self, 1);
    
    memcpy(self->array, elem, self->size);
    self->quantity++;
}

/* FUNCOES DE REMOCAO */
bool pop_back_ArrayList(ArrayList *self)
{
    if(empty_ArrayList(self))
        return 0;

    self->quantity--;
    return 1;
}
bool pop_front_ArrayList(ArrayList *self)
{
    if(empty_ArrayList(self))
        return 0;
    shift_ArrayList(self, -1);
    self->quantity--;
    return 1;
}
void *pop_back_data_ArrayList(ArrayList *self)
{
    if(empty_ArrayList(self))
        return NULL;
    void* data = memcpy(data, end_ArrayList(self), self->size);
    
    self->quantity--;
    return data;
}
void *pop_front_data_ArrayList(ArrayList *self)
{
    if(empty_ArrayList(self))
        return NULL;
    void* data = memcpy(data, end_ArrayList(self), self->size);
    
    shift_ArrayList(self, -1);

    self->quantity--;
    return data;
}

/* FUNCOES AUXILIARES */
void resize_ArrayList(ArrayList *self, int new_length)
{
    if(new_length > 0)
    {
        resize_array(&self->array, self->length, new_length, self->size);
        
        self->length = new_length;

        if(self->quantity > new_length)
            self->quantity = new_length;
    }
}
void shrink_ArrayList(ArrayList *self)
{
    resize_ArrayList(self, self->quantity);
}

void shift_ArrayList(ArrayList *self, int n_shift)
{
    if(n_shift != 0)
    {
        if(!full_ArrayList(self))
            resize_ArrayList(self, self->quantity);
        
        shift_array(&self->array, self->length, n_shift, self->size);
        
        self->length = self->length + n_shift;
    }
}
bool empty_ArrayList(ArrayList *self)
{
    return self->quantity == 0;
}
bool full_ArrayList(ArrayList *self)
{
    return self->quantity == self->length;
}

void* begin_ArrayList(ArrayList *self)
{
    return self->array;
}
void* end_ArrayList(ArrayList *self)
{
    return self->array + (self->quantity - 1) * self->size;
}

void* clear_ArrayList(ArrayList *self)
{
    self->quantity = 0;
}


void print_ArrayList(ArrayList *self, void (*print)(const void*))
{
    print_array(self->array, self->quantity, self->size, print);
}
void println_ArrayList(ArrayList *self, void (*print)(const void*))
{
    println_array(self->array, self->quantity, self->size, print);
}
void print_if_ArrayList(ArrayList *self, void (*print)(const void*), int (*condition)(const void*))
{
    print_if_array(self->array, self->quantity, self->size, print, condition);
}

ArrayList* random_int_ArrayList(int begin, int end, int length)
{
    if(length <= 0) return NULL;

    ArrayList* new = (ArrayList*) malloc(sizeof(ArrayList));

    new->array    = random_array(begin, end, length);
    new->length   = length;
    new->size     = sizeof(int);
    new->quantity = length;

    return new;
}
#endif