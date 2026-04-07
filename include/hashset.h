#ifndef _HASH_SET_H
#define _HASH_SET_H

#include "memclass.h"
#include "arraylist.h"
#include "linkedlist.h"

#define HS_MAX_LOAD_FACTOR 0.8

typedef struct _hash_table {
    ArrayList *list;
    uint16_t size_elements;
    size_t count;
	compare_fn compare_function;
	destroy_fn destroy_function;
} HashSet;

HashSet *hs_create(size_t size_elements);
HashSet *hs_create_comparator(size_t size_elements, compare_fn compare_function);
HashSet *hs_create_destroyer(size_t size_elements, destroy_fn destroy_function);
HashSet *hs_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void     hs_change_comparator(HashSet *hs, compare_fn compare_function);
void     hs_change_destroyer(HashSet *hs, destroy_fn destroy_function);

uint64_t hs_hash_function(void *val, size_t size_element);
size_t hs_hash_val(HashSet *hs, void *val, size_t size_elements);
float hs_load_factor(HashSet *hs);
bool hs_add_val(HashSet *hs, void *val, size_t position);//do not use, useful for hashmap only
bool hs_rehash(HashSet *hs);//do not use, useful for hashmap only

bool hs_add(HashSet *hs, void *val);

bool hs_has_pos(HashSet *hs, void *val, size_t position);
bool hs_has(HashSet *hs, void *val);

bool hs_remove(HashSet *hs, void *val);

bool   hs_is_empty(HashSet *hs);
size_t hs_size(HashSet *hs);

bool hs_destroy(HashSet **hs);

#endif

