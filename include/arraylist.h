#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "memclass.h"
#include "iter.h"

typedef struct _arrlist {
    void *elements;
    size_t count;
    size_t len;
    size_t size_elements;
	compare_fn compare_function;
	destroy_fn destroy_function;
} ArrayList;

ArrayList *al_create(size_t element_size, compare_fn compare_function, destroy_fn destroy_function);
ArrayList *al_create_sized(size_t element_size, size_t len, compare_fn compare_function, destroy_fn destroy_function);
bool       al_realloc(ArrayList *list);

bool al_input_unsafe(ArrayList *list, void *new_element, size_t position);
bool al_add(ArrayList *list, void *new_element);
bool al_push(ArrayList *list, void *new_element);
bool al_add_at(ArrayList *list, void *new_element, size_t pos);
bool al_add_many(ArrayList *list, void *elements, size_t elements_count);
bool al_add_many_at(ArrayList *list, void *elements, size_t elements_count, size_t pos);
bool al_update(ArrayList *list, void *update, size_t pos);

ArrayList *al_copy_list(ArrayList *list);
void al_concat_list(ArrayList *l1, ArrayList *l2);
ArrayList *al_concat_list_new(ArrayList *l1, ArrayList *l2);

size_t al_size(ArrayList *list);
bool al_is_empty(ArrayList *list);
bool al_has(ArrayList *list, void *val, size_t *pos);
bool al_has_at(ArrayList *list, void *val, size_t pos);

void *al_get_ith(ArrayList *list, size_t i);

bool al_sort(ArrayList *list);
void al_iterate(ArrayList *list, iter_fn func, void *arg);

bool al_remove_at(ArrayList *list, size_t pos, void *out_ptr);
bool al_remove_at_fast(ArrayList *list, size_t pos, void *out_ptr); /*changes array order*/
bool al_pop(ArrayList *list, void *out_ptr);
bool al_remove_first(ArrayList *list, void *out_ptr);
bool al_remove_val(ArrayList *list, void *val);

bool al_clear(ArrayList *list);
bool al_destroy(ArrayList **list);

#endif
