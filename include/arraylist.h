<<<<<<< HEAD:include/arraylist.h
#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _arrlist {
    void *elements;
    size_t count;
    size_t len;
    size_t size_elements;
} ArrayList;

ArrayList *al_alloc();
ArrayList *al_create(size_t element_size);
ArrayList *al_create_sized(size_t element_size, size_t len);
bool       al_realloc_array_list(ArrayList *list);

bool al_input_unsafe(ArrayList *list, void *new_element, size_t element_size, size_t position);
bool al_append_element(ArrayList *list, void *new_element, size_t element_size);
bool al_push(ArrayList *list, void *new_element, size_t element_size);
bool al_append_many(ArrayList *list, void *elements, size_t elements_count, size_t elements_size);

ArrayList *al_copy_list(ArrayList *list);
ArrayList *al_concat_lists(ArrayList *l1, ArrayList *l2);

bool al_is_array_list_empty(ArrayList *list);
bool al_has(ArrayList *list, void *val, size_t element_size, size_t *pos);
bool al_has_at(ArrayList *list, void *val, size_t element_size, size_t pos);

void *al_get_ith(ArrayList *list, size_t i);
void *al_remove_at(ArrayList *list, size_t pos);
void *al_pop(ArrayList *list);
void *al_dequeue(ArrayList *list);
bool  al_remove_val(ArrayList *list, void *val, size_t element_size);

bool al_destroy(ArrayList **list);

#endif
=======
#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _arrlist {
    void *elements;
    size_t count;
    size_t len;
    size_t size_elements;
} ArrayList;

ArrayList *al_create_array_list();
ArrayList *al_alloc_array_list(size_t element_size);
ArrayList *al_alloc_array_list_sized(size_t element_size, size_t len);
bool       al_realloc_array_list(ArrayList *list);

bool al_input_unsafe(ArrayList *list, void *new_element, size_t element_size, size_t position);
bool al_append_element(ArrayList *list, void *new_element, size_t element_size);
bool al_push(ArrayList *list, void *new_element, size_t element_size);
bool al_append_many(ArrayList *list, void *elements, size_t elements_count, size_t elements_size);

ArrayList *al_copy_list(ArrayList *list);
ArrayList *al_concat_lists(ArrayList *l1, ArrayList *l2);

bool al_is_array_list_empty(ArrayList *list);
bool al_has(ArrayList *list, void *val, size_t element_size, size_t *pos);
bool al_has_at(ArrayList *list, void *val, size_t element_size, size_t pos);

void *al_get_ith(ArrayList *list, size_t i);
void *al_remove_at(ArrayList *list, size_t pos);
void *al_pop(ArrayList *list);
void *al_dequeue(ArrayList *list);
bool  al_remove_val(ArrayList *list, void *val, size_t element_size);

bool al_free_array_list(ArrayList *list);

#endif
>>>>>>> d08a5d5df234869e3cb60b3b662f9a323004031c:hash/include/arraylist.h
