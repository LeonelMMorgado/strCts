<<<<<<< HEAD:include/hash.h
#ifndef _HASH_H
#define _HASH_H

#define HT_MAX_LOAD_FACTOR 0.8

#include "arraylist.h"
#include "linkedlist.h"

typedef struct _ht_entry {
    LinkedList *elements;
    bool valid_entry;
} HashEntry;

typedef struct _hash_table {
    ArrayList *list;
    uint16_t size_element;
    size_t elements_count;
} HashTable;

HashTable *ht_create(size_t element_size);
bool rehash(HashTable *ht);

uint64_t ht_hash_function(void *val, size_t element_size);
size_t ht_hash_val(HashTable *ht, void *val, size_t element_size);
float ht_load_factor(HashTable *ht);

bool ht_has(HashTable *ht, void *val, size_t element_size, size_t position);
bool ht_insert(HashTable *ht, void *val, size_t element_size);

bool ht_destroy(HashTable **ht);

#endif

=======
#ifndef _HASH_H
#define _HASH_H

#define HT_MAX_LOAD_FACTOR 0.8

typedef struct _ht_entry {
    LinkedList *elements;
    bool valid_entry;
} HashEntry;

typedef struct _hash_table {
    ArrayList *list;
    uint16_t size_element;
    size_t elements_count;
} HashTable;

HashTable *ht_init_table(size_t element_size);
bool rehash(HashTable *ht);

uint64_t ht_hash_function(void *val, size_t element_size);
size_t ht_hash_val(HashTable *ht, void *val, size_t element_size);
float ht_load_factor(HashTable *ht);

bool ht_has(HashTable *ht, void *val, size_t element_size, size_t position);
bool ht_insert(HashTable *ht, void *val, size_t element_size);
// bool ht_add_val(HashTable *ht, void *val, size_t element_size, size_t position);

bool ht_free(HashTable *ht);

#endif
>>>>>>> d08a5d5df234869e3cb60b3b662f9a323004031c:hash/hash.h
