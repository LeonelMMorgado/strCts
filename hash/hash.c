#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <linkedlist.h>
#include <arraylist.h>

#define HT_MAX_LOAD_FACTOR 0.8

/*
    THIS CODE ONLY SUPPORTS SAME TYPE HASH ENTRIES
*/

typedef struct _ht_entry {
    LinkedList *elements;
    bool valid_entry;
} HashEntry;

typedef struct _hash_table {
    ArrayList *list;
    uint16_t size_element;
    size_t elements_count;
} HashTable;

HashTable *ht_init_table(size_t element_size) {
    HashTable *ht = malloc(sizeof(*ht));
    if(!ht) return NULL;
    ht->list = al_alloc_array_list(sizeof(HashEntry));
    if(!ht->list) {
        free(ht);
        return NULL;
    }
    for(size_t i = 0; i < ht->list->len; i++) {
        ((HashEntry *)ht->list->elements)[i].valid_entry = false;
        ((HashEntry *)ht->list->elements)[i].elements = NULL;
    }
    ht->list->count = ht->list->len;
    ht->size_element = element_size;
    ht->elements_count = 0;
    return ht;
}

uint64_t ht_hash_function(void *val, size_t element_size) {
    uint64_t hash = 0;
    uint8_t *c = val;
    for(size_t i = 0; i < element_size; i++)
        hash = (hash * 31) + c[i];
    return hash;
}

size_t ht_hash_val(HashTable *ht, void *val, size_t element_size) {
    return ht_hash_function(val, element_size) % ht->list->len;
}

float ht_load_factor(HashTable *ht) {
    return (float)ht->elements_count/ht->list->len;
}

bool ht_has(HashTable *ht, void *val, size_t element_size, size_t position) {
    if(!ht || !val) return false;
    if(ht->size_element != element_size) return false;
    return ll_get_node(((HashEntry*)al_get_ith(ht->list, position))->elements, val) != NULL;
}

bool ht_add_val(HashTable *ht, void *val, size_t element_size, size_t position) {
    if(!ht || !val) return false;
    if(ht->size_element != element_size) return false;
    HashEntry*ith = (HashEntry*)al_get_ith(ht->list, position);
    if(!ith->valid_entry)
        ith->valid_entry = true;
    if(ith->elements == NULL)
        ith->elements = ll_alloc_linked_list(element_size);
    return ll_append_tail(ith->elements, val, ht->size_element);
}

bool rehash(HashTable *ht) {
    ArrayList *new = al_alloc_array_list_sized(sizeof(HashEntry), ht->list->len * 2);
    new->count = new->len;
    for(size_t i = 0; i < new->len; i++) {
        HashEntry*ith = al_get_ith(new->elements, i);
        ith->valid_entry = false;
        ith->elements = NULL;
    }
    for(size_t i = 0; i < ht->list->len; i++) {
        HashEntry *elements_at_i = al_get_ith(ht->list, i);
        if(!elements_at_i->valid_entry || !elements_at_i->elements) continue;
        LLNode *p = elements_at_i->elements->head;
        if(!p) continue;
        for(size_t j = 0; j < elements_at_i->elements->len; j++) {
            size_t ith = ht_hash_function(p->element, ht->size_element) % new->len;
            HashEntry *new_entry = al_get_ith(new, ith);
            new_entry->valid_entry = true;
            if(!new_entry->elements)
                new_entry->elements = ll_alloc_linked_list(ht->size_element);
            ll_append_tail(new_entry->elements, p->element, ht->size_element);
        }
        ll_free(elements_at_i->elements);
    }
    al_free_array_list(ht->list);
    ht->list = new;
    return true;
}

bool ht_insert(HashTable *ht, void *val, size_t element_size) {
    if(!ht || !val) return false;
    if(ht->size_element != element_size) return false;
    size_t pos = ht_hash_val(ht, val, element_size);
    if(ht_has(ht, val, element_size, pos)) return false;
    if(ht_add_val(ht, val, element_size, pos)) ht->elements_count++;
    if(ht_load_factor(ht) > HT_MAX_LOAD_FACTOR) return rehash(ht);
    return true;
}
