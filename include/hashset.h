#ifndef _HASH_SET_H
#define _HASH_SET_H

#define HS_MAX_LOAD_FACTOR 0.8

#include "arraylist.h"
#include "linkedlist.h"

typedef struct _hs_entry {
    LinkedList *elements;
    bool valid_entry;
} HashEntry;

typedef struct _hash_table {
    ArrayList *list;
    uint16_t size_element;
    size_t elements_count;
} HashSet;

HashSet *hs_create(size_t element_size);

uint64_t hs_hash_function(void *val, size_t element_size);
size_t hs_hash_val(HashSet *hs, void *val, size_t element_size);
float hs_load_factor(HashSet *hs);

bool hs_has(HashSet *hs, void *val, size_t element_size, size_t position);
bool hs_add(HashSet *hs, void *val, size_t element_size);

void *hs_remove(HashSet *hs, void *val, size_t element_size);

bool hs_is_empty(HashSet *hs);
size_t hs_size(HashSet *hs);

bool hs_destroy(HashSet **hs);

#endif

