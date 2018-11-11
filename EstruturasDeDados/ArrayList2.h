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

// ------------------------------------------ //
//      Funcoes de construir e destruir       //
// ------------------------------------------ //
ArrayList* new_ArrayList(size_t size, int length);  // 10/11/2018
void delete_ArrayList(ArrayList **self);            // 10/11/2018
void delete_with_ArrayList(ArrayList **self, void (*delete)(const void*)); // TODO
ArrayList* dup_ArrayList(ArrayList *self);          // 10/11/2018
// ------------------------------------------ //
//             Funcoes de insercao            //
// ------------------------------------------ //
bool push_back_ArrayList(ArrayList *self, void *value);  // 10/11/2018
bool push_front_ArrayList(ArrayList *self, void *value); // 10/11/2018
bool insert_ArrayList(ArrayList *self, void *value, int pos);
bool set_in_ArrayList(ArrayList *self, void *value, int pos);
// ------------------------------------------ //
//              Funcoes de remocao            //
// ------------------------------------------ //
bool pop_back_ArrayList(ArrayList *self);        // 10/11/2018
bool pop_front_ArrayList(ArrayList *self);       // 10/11/2018
void *pop_back_data_ArrayList(ArrayList *self);  // 10/11/2018
void *pop_front_data_ArrayList(ArrayList *self); // 10/11/2018
// ------------------------------------------ //
//            Funcoes de manipulacao          //
// ------------------------------------------ //
void unique_ArrayList(ArrayList *self, int (*cmp)(const void *, const void *));
void sort_ArrayList(ArrayList *self, int (*cmp)(const void *, const void *));
void reverse_ArrayList(ArrayList *self);

void resize_ArrayList(ArrayList *self, int length); // 10/11/2018
void shrink_ArrayList(ArrayList *self);             // 10/11/2018
void shift_ArrayList(ArrayList *self, int n_shift); // 10/11/2018
void clear_ArrayList(ArrayList *self);              // 10/11/2018

void swap_ArrayList(ArrayList *arraylist1, ArrayList *arraylist2);

ArrayList* random_int_ArrayList(int begin, int end, int length); // 10/11/2018
// ------------------------------------------ //
//            Funcoes de verificacao          //
// ------------------------------------------ //
int equals_ArrayList(ArrayList *arraylist1, ArrayList *arraylist2, int (*cmp)(const void *, const void *));

bool empty_ArrayList(ArrayList *self); // 10/11/2018
bool full_ArrayList(ArrayList *self);  // 10/11/2018

bool is_sorted_ArrayList(ArrayList *self, int (*cmp)(const void*, const void*));
bool is_reversed_ArrayList(ArrayList *self, int (*cmp)(const void*, const void*));
// ------------------------------------------ //
//              Funcoes de impressao          //
// ------------------------------------------ //
void print_ArrayList(ArrayList *self, void (*print)(const void*));
void println_ArrayList(ArrayList *self, void (*print)(const void*));
void print_if_ArrayList(ArrayList *self, void (*print)(const void*), int (*condition)(const void*));
// ------------------------------------------ //
//              Funcoes de iteracao           //
// ------------------------------------------ //
void* begin_ArrayList(ArrayList *self); // 10/11/2018
void* end_ArrayList(ArrayList *self);   // 10/11/2018



/* Implementacoes ArrayList */



// ------------------------------------------ //
//      Funcoes de construir e destruir       //
// ------------------------------------------ //
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
ArrayList* dup_ArrayList(ArrayList *self)
{
    ArrayList* new = malloc(sizeof(ArrayList));
    new->array = copy_array(
        malloc(self->size * self->length),
        self->array,
        self->quantity,
        self->size
        );
    new->quantity = self->quantity;
    new->length = self->length;
    new->size = self->size;
    
    return new;
}
// ------------------------------------------ //
//             Funcoes de insercao            //
// ------------------------------------------ //
bool push_back_ArrayList(ArrayList *self, void *value)
{
    if(full_ArrayList(self))
        resize_ArrayList(
            self,
            self->length + 1
            );
    
    memcpy(
        end_ArrayList(self) + self->size,
        value,
        self->size
        );
    self->quantity++;
}
bool push_front_ArrayList(ArrayList *self, void *value)
{
    if(full_ArrayList(self))
        shift_ArrayList(self, 1);
    else
        rcopy_array(
            self->array + self->size,
            self->array,
            self->quantity,
            self->size
            );
    
    memcpy(self->array, value, self->size);
    self->quantity++;
}
bool insert_ArrayList(ArrayList *self, void *value, int pos)
{
    if(pos < 0) pos = self->quantity + pos + 1;
    if(pos < 0) return 0;


    if(self->quantity == pos)
    {   
        push_back_ArrayList(self, value);
        return 1;
    }
    else if(0 == pos)
    {   
        push_front_ArrayList(self, value);
        return 1;
    }
    else if(self->quantity >= self->length)
        resize_ArrayList(self, self->length + 1);

    rcopy_array(
        self->array + (pos + 1) * self->size,
        self->array + pos * self->size,
        self->quantity - pos,
        self->size
        );
    memcpy(
        self->array + pos * self->size, 
        value, 
        self->size
        );
    self->quantity++;
    return 1;
}
bool set_in_ArrayList(ArrayList *self, void *value, int pos)
{
    if(pos >= self->quantity) return 0;
    if(pos < 0) pos = self->quantity + pos;
    if(pos < 0) return 0;
    memcpy(
        self->array + self->size * pos,
        value,
        self->size
        );
    return 1;
}
// ------------------------------------------ //
//              Funcoes de remocao            //
// ------------------------------------------ //
bool pop_back_ArrayList(ArrayList *self)
{
    void* data = pop_back_data_ArrayList(self);
    if(data)
    {
        free(data);
        return 1;
    }
    return 0;
}
bool pop_front_ArrayList(ArrayList *self)
{
    void* data = pop_front_data_ArrayList(self);
    if(data)
    {
        free(data);
        return 1;
    }
    return 0;
}
void *pop_back_data_ArrayList(ArrayList *self)
{
    if(empty_ArrayList(self))
        return NULL;
    void* data = memcpy(
        malloc(self->size), 
        end_ArrayList(self), 
        self->size
        );
    
    self->quantity--;
    return data;
}
void *pop_front_data_ArrayList(ArrayList *self)
{
    if(empty_ArrayList(self))
        return NULL;
    void* data = memcpy(
        malloc(self->size),
        end_ArrayList(self),
        self->size
        );
    
    copy_array(
        self->array,
        self->array + self->size,
        self->quantity--,
        self->size
        );
    return data;
}

// ------------------------------------------ //
//            Funcoes de manipulacao          //
// ------------------------------------------ //
void unique_ArrayList(ArrayList *self, int (*cmp)(const void *, const void *))
{
    self->quantity = unique_array(
        self->array,
        self->quantity,
        self->size,
        cmp
        );
}
void sort_ArrayList(ArrayList *self, int (*cmp)(const void *, const void *))
{
    qsort(self->array, self->quantity, self->size, cmp);
}
void reverse_ArrayList(ArrayList *self)
{
    reverse_array(self->array, self->quantity, self->size);
}

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
void clear_ArrayList(ArrayList *self)
{
    self->quantity = 0;
}

void swap_ArrayList(ArrayList *arraylist1, ArrayList *arraylist2)
{
    pswap(arraylist1->array, arraylist2->array);
    swap(&arraylist1->quantity, &arraylist2->quantity, sizeof(int));
    swap(&arraylist1->length, &arraylist2->length, sizeof(int));
    swap(&arraylist1->size, &arraylist2->size, sizeof(size_t));
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
// ------------------------------------------ //
//            Funcoes de verificacao          //
// ------------------------------------------ //
int equals_ArrayList(ArrayList *arraylist1, ArrayList *arraylist2, int (*cmp)(const void *, const void *))
{
    if (arraylist1->quantity != arraylist2->quantity)
        return false;
    if (arraylist1->size != arraylist2->size)
        return false;
    
    return equals_array(
        arraylist1->array,
        arraylist2->array,
        arraylist1->quantity,
        arraylist1->size,
        cmp
        );
}
bool empty_ArrayList(ArrayList *self)
{
    return self->quantity == 0;
}
bool full_ArrayList(ArrayList *self)
{
    return self->quantity == self->length;
}
bool is_sorted_ArrayList(ArrayList *self, int (*cmp)(const void*, const void*))
{
    return is_sorted_array(self->array, self->quantity, self->size, cmp);
}
bool is_reversed_ArrayList(ArrayList *self, int (*cmp)(const void*, const void*))
{
    return is_reversed_array(self->array, self->quantity, self->size, cmp);
}
// ------------------------------------------ //
//              Funcoes de iteracao           //
// ------------------------------------------ //
void* begin_ArrayList(ArrayList *self)
{
    return self->array;
}
void* end_ArrayList(ArrayList *self)
{
    return self->array + (self->quantity - 1) * self->size;
}
// ------------------------------------------ //
//              Funcoes de impressao          //
// ------------------------------------------ //
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

#endif