#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <linkedlist.h>
#include <arraylist.h>
#include <hashset.h>

HashSet *hs_create(size_t size_elements) {
	return hs_create_full(size_elements, NULL, NULL);
}

HashSet *hs_create_comparator(size_t size_elements, compare_fn compare_function) {
	return hs_create_full(size_elements, compare_function, NULL);
}

HashSet *hs_create_destroyer(size_t size_elements, destroy_fn destroy_function) {
	return hs_create_full(size_elements, NULL, destroy_function);
}

HashSet *hs_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
    HashSet *hs = malloc(sizeof(*hs));
    if(!hs) return NULL;
    hs->list = al_create(sizeof(HashEntry));
    if(!hs->list) {
        free(hs);
        return NULL;
    }
    for(size_t i = 0; i < hs->list->len; i++) {
        ((HashEntry *)hs->list->elements)[i].valid_entry = false;
        ((HashEntry *)hs->list->elements)[i].element = NULL;
    }
    hs->list->count = hs->list->count;
    hs->size_elements = size_elements;
    hs->count = 0;
	if(compare_function) hs->compare_function = compare_function;
	else hs->compare_function = &memcmp;
	hs->destroy_function = destroy_function;
    return hs;
}

void hs_change_comparator(HashSet *hs, compare_fn compare_function) {
	if(!hs || !compare_function) return;
	hs->compare_function = compare_function;
}

void hs_change_destroyer(HashSet *hs, destroy_fn destroy_function) {
	if(!hs || !destroy_function) return;
	hs->destroy_function = destroy_function;
}

uint64_t hs_hash_function(void *val, size_t size_element) {
    if(!val) return 0;
    uint64_t hash = 0;
    uint8_t *c = val;
    for(size_t i = 0; i < size_element; i++)
        hash = (hash * 31) + c[i];
    return hash;
}

size_t hs_hash_val(HashSet *hs, void *val, size_t size_element) {
    if(!hs || !val) return 0;
    return hs_hash_function(val, size_element) % hs->list->len;
}

float hs_load_factor(HashSet *hs) {
    if(!hs) return -1;
    return (float)hs->count/hs->list->count;
}

bool hs_has(HashSet *hs, void *val, size_t position) {
    if(!hs || !val) return false;
    return ll_get_node(((HashEntry*)al_get_ith(hs->list, position))->element, val) != NULL;
}

bool hs_add_val(HashSet *hs, void *val, size_t position) {
    if(!hs || !val) return false;
    HashEntry*ith = (HashEntry*)al_get_ith(hs->list, position);
    if(!ith->valid_entry)
        ith->valid_entry = true;
    if(ith->element == NULL)
        ith->element = ll_create_full(hs->size_elements, hs->compare_function, hs->destroy_function);
    return ll_add_tail(ith->element, val);
}

bool hs_rehash(HashSet *hs) {
    if(!hs) return false;
    ArrayList *new = al_create_sized(sizeof(HashEntry), hs->list->count * 2);
    new->count = new->count;
    for(size_t i = 0; i < new->count; i++) {
        HashEntry*ith = al_get_ith(new, i);
        ith->valid_entry = false;
        ith->element = NULL;
    }
    for(size_t i = 0; i < hs->list->count; i++) {
        HashEntry *elements_at_i = al_get_ith(hs->list, i);
        if(!elements_at_i->valid_entry || !elements_at_i->element) continue;
		LinkedList *elements = elements_at_i->element;
        LLNode *p = elements->head;
        if(!p) continue;
        for(size_t j = 0; j < elements->count; j++) {
            size_t ith = hs_hash_function(p->element, hs->size_elements) % new->count;
            HashEntry *new_entry = al_get_ith(new, ith);
            new_entry->valid_entry = true;
            if(!new_entry->element)
                new_entry->element = ll_create_full(hs->size_elements, hs->compare_function, hs->destroy_function);
            ll_add_tail(new_entry->element, p->element);
        }
        ll_destroy(&elements);
    }
    al_destroy(&(hs->list));
    hs->list = new;
    return true;
}

bool hs_add(HashSet *hs, void *val) {
    if(!hs || !val) return false;
    size_t pos = hs_hash_val(hs, val, hs->size_elements);
    if(hs_has(hs, val, pos)) return false;
    if(hs_add_val(hs, val, pos)) hs->count++;
    if(hs_load_factor(hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hs);
    return true;
}

bool hs_remove(HashSet *hs, void *val) {
    if(!hs || !val) return NULL;
    HashEntry *ith = al_get_ith(hs->list, hs_hash_val(hs, val, hs->size_elements));
	bool r = ll_remove_val(ith->element, val);
	if(r) hs->count--;
	return r;
}

bool hs_is_empty(HashSet *hs) {
    if(!hs) return false;
    return hs->count == 0;
}

size_t hs_size(HashSet *hs) {
    if(!hs) return 0;
    return hs->count;
}

bool hs_destroy(HashSet **hs) {
    if(!hs) return false;
    if(!*hs) return false;
    for(size_t i = 0; i < (*hs)->list->count; i++) {
		LinkedList *list = (((HashEntry*)al_get_ith((*hs)->list, i))->element);
        ll_destroy(&list);
	}
	al_destroy(&((*hs)->list));
    free(*hs);
    *hs = NULL;
    return true;
}

