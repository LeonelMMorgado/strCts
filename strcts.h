#ifndef _STRCTS_H
#define _STRCTS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

typedef int (*compare_fn)(const void *val1, const void *val2, size_t size_element);
typedef void (*destroy_fn)(void *element);
typedef void (*iter_fn)(void *element, void *arg);

//DynamicArray definitions
#define INITIAL_ARRAY_CAPACITY 256
typedef struct _dynamic_array_header {
	size_t len;
	size_t count;
} ArrayHeader;

//ArrayList definitions
typedef struct _arrlist {
    void *elements;
    size_t count;
    size_t len;
    size_t size_elements;
	compare_fn compare_function;
	destroy_fn destroy_function;
} ArrayList;

//LinkedList definitions
typedef struct _llnode LLNode; 
struct _llnode {
    void *element;
    LLNode *next;
    LLNode *before;
};
typedef struct _llist {
    LLNode *head;
    LLNode *tail;
    size_t size_elements;
    size_t count;
	compare_fn compare_function;
	destroy_fn destroy_function;
} LinkedList;

//HashSet definitions
#define HS_MAX_LOAD_FACTOR 0.8
typedef struct _hs_entry {
    void *element;
    bool valid_entry;
} HashEntry;
typedef struct _hash_table {
    ArrayList *list;
    uint16_t size_elements;
    size_t count;
	compare_fn compare_function;
	destroy_fn destroy_function;
} HashSet;

//HashMap definitions
typedef struct _hash_map_pair {
	void *key;
	void *value;
} HashMapPair;
typedef struct _hash_map {
	HashSet *hs;
	size_t size_key;
	size_t size_value;
	compare_fn compare_key;
	compare_fn compare_value;
	destroy_fn destroy_key;
	destroy_fn destroy_value;
} HashMap;

//BinaryTree definitions
typedef struct _bstree_node {
	void *element;
	struct _bstree_node *left;
	struct _bstree_node *right;
	int64_t height;
} BinaryTreeNode;
typedef struct _binary_search_tree {
    size_t size_elements;
    BinaryTreeNode *root;
	compare_fn compare_function;
	destroy_fn destroy_function;
} BinaryTree;

//AbstractTree definitions
typedef struct _abstract_tree {
	void *element;
	size_t size_elements;
	struct _abstract_tree *child;
	struct _abstract_tree *sibling;
	compare_fn compare_function;
	destroy_fn destroy_function;
} AbstractTree;

#ifdef __cplusplus
extern "C" {
#endif

int int_compare(const void *val1, const void *val2, size_t size_element);
int uint_compare(const void *val1, const void *val2, size_t size_element);
int i64_compare(const void *val1, const void *val2, size_t size_element);
int u64_compare(const void *val1, const void *val2, size_t size_element);
int float_compare(const void *val1, const void *val2, size_t size_element);
int double_compare(const void *val1, const void *val2, size_t size_element);
int string_compare(const void *val1, const void *val2, size_t size_element);
void pointer_destroy(void *element);

//ArrayList functions
ArrayList *al_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
ArrayList *al_create_sized(size_t size_elements, size_t len, compare_fn compare_function, destroy_fn destroy_function);
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

//LinkedList functions
LinkedList *ll_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
bool ll_add_tail(LinkedList *list, void *val);
bool ll_add_head(LinkedList *list, void *val);
bool ll_add_at(LinkedList *list, void *val, size_t pos);
bool ll_add_many(LinkedList *list, void *elements, size_t elements_count);
bool ll_add_many_at(LinkedList *list, void *elements, size_t elements_count, size_t pos);
LinkedList *ll_copy_list(LinkedList *list);
void ll_concat_list(LinkedList *list1, LinkedList *list2);
LinkedList *ll_concat_list_new(LinkedList *list1, LinkedList *list2);
LLNode *ll_get_node(LinkedList *list, void *val);
LLNode *ll_get_node_at(LinkedList *list, size_t pos);
void ll_iterate(LinkedList *list, iter_fn func, void *arg);
bool ll_remove_tail(LinkedList *list, void *out_ptr);
bool ll_remove_head(LinkedList *list, void *out_ptr);
bool ll_remove_val(LinkedList *list, void *val);
bool ll_remove_at(LinkedList *list, size_t pos, void *out_ptr);
void ll_destroy(LinkedList **list);

//HashSet functions
HashSet *hs_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
uint64_t hs_hash_function(void *val, size_t size_element);
size_t hs_hash_val(HashSet *hs, void *val, size_t size_elements);
float hs_load_factor(HashSet *hs);
bool hs_add_val(HashSet *hs, void *val, size_t position);//do not use, useful for hashmap only
bool hs_rehash(HashSet *hs);//do not use, useful for hashmap only
bool hs_add(HashSet *hs, void *val);
bool hs_has(HashSet *hs, void *val, size_t position);
bool hs_remove(HashSet *hs, void *val);
bool hs_is_empty(HashSet *hs);
size_t hs_size(HashSet *hs);
bool hs_destroy(HashSet **hs);

//HashMap functions
HashMap *hm_create(size_t size_key, size_t size_value, compare_fn compare_key, compare_fn compare_value, destroy_fn destroy_key, destroy_fn destroy_value);
bool hm_add(HashMap *hm, void *key, void *value);
bool hm_has_key(HashMap *hm, void *key);
bool hm_has_value(HashMap *hm, void *value); /*O(n) search*/
void*hm_get_value(HashMap *hm, void *key); /*basically doing hm[key] <- returns the pointer to value*/
void*hm_get_key(HashMap *hm, void *value); /*O(n) search */
bool hm_remove_key(HashMap *hm, void *key); //removes pair from map by finding key
bool hm_remove_value(HashMap *hm, void *value); //removes pair from map in O(n) by value
bool hm_is_empty(HashMap *hm);
size_t hm_size(HashMap *hm);
size_t hm_struct_size(HashMap *hm);
bool hm_destroy(HashMap **hm);

//BinaryTree functions
BinaryTreeNode *bt_create_node(void *val, size_t size_elements);
BinaryTree *bt_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
int64_t bt_height(BinaryTreeNode *root);
void bt_update_height(BinaryTreeNode *root);
int64_t bt_balance(BinaryTreeNode *root);
bool bt_is_balanced(BinaryTreeNode *root);
bool bt_insert(BinaryTree *tree, void *val);
bool bt_remove(BinaryTree *tree, void *val);
BinaryTreeNode *bt_search(BinaryTree *tree, void *val);
// BinaryTreeNode *bt_invert_tree(BinaryTreeNode *root);
void bt_print(BinaryTree *tree, int rows, int cols);
void bt_delete_node(BinaryTreeNode *node, destroy_fn destroy_function);
void bt_delete(BinaryTree **tree);

//AbstractTree functions
AbstractTree *at_create(void *val, size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void at_add_child(AbstractTree* parent, AbstractTree* child);
void at_print_tree(AbstractTree *tree);
bool at_destroy(AbstractTree **tree);

#ifdef __cplusplus
}
#endif

#endif //_STRCTS_H

#ifdef STRCTS_IMPLEMENTATION

int int_compare(const void *val1, const void *val2, size_t size_element) {
	int v1 = *(int*)val1;
	int v2 = *(int*)val2;
	return (v1 > v2) - (v1 < v2);
}

int uint_compare(const void *val1, const void *val2, size_t size_element) {
	unsigned int v1 = *(unsigned int*)val1;
	unsigned int v2 = *(unsigned int*)val2;
	return (v1 > v2) - (v1 < v2);
}

int i64_compare(const void *val1, const void *val2, size_t size_element) {
	int64_t v1 = *(int64_t*)val1;
	int64_t v2 = *(int64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int u64_compare(const void *val1, const void *val2, size_t size_element) {
	uint64_t v1 = *(uint64_t*)val1;
	uint64_t v2 = *(uint64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int float_compare(const void *val1, const void *val2, size_t size_element) {
	float v1 = *(float*)val1;
	float v2 = *(float*)val2;
	return (v1 > v2) - (v1 < v2);
}

int double_compare(const void *val1, const void *val2, size_t size_element) {
	double v1 = *(double*)val1;
	double v2 = *(double*)val2;
	return (v1 > v2) - (v1 < v2);
}

int string_compare(const void *val1, const void *val2, size_t size_element) {
	char *s1 = *(char**)val1;
	char *s2 = *(char**)val2;
	return strcmp(s1, s2);
}

void pointer_destroy(void *val) {
	if(!val) return;
	free(*(void **)val);
}

#define array_create(array) \
	do { \
		ArrayHeader *h = malloc(sizeof(ArrayHeader) + (sizeof(*(array)) * INITIAL_ARRAY_CAPACITY)); \
		h->len = INITIAL_ARRAY_CAPACITY; \
		h->count = 0; \
		(array) = (void*)(h + 1); \
	} while(0)

#define array_create_sized(array, size) \
	do { \
		ArrayHeader *h = malloc(sizeof(ArrayHeader) + (sizeof(*(array)) * (size))); \
		h->len = (size); \
		h->count = 0; \
		(array) = (void*)(h + 1); \
	} while(0)

#define array_input_unsafe(array, x, pos) (array)[(pos)] = (x)

#define array_add(array, x) \
	do { \
		if(!(array)) { \
			array_create((array)); \
		} \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		if(h->count == h->len) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		(array)[h->count++] = (x); \
	} while(0)

#define array_push(array, x) array_add((array), (x))

#define array_add_at(array, x, pos) \
	do { \
		if(!(array)) array_create((array)); \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		if(h->count == h->len) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		memmove((array) + (pos) + 1, (array) + (pos), sizeof(*(array)) * (h->count - pos)); \
		(array)[(pos)] = (x); \
		h->count++; \
	} while(0)

#define array_add_many(array, elements, elements_count) \
	do { \
		if(!(array)) array_create((array)); \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		while(h->len - h->count < elements_count) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		memmove((array) + h->count, elements, elements_count * sizeof(*(array))); \
		h->count += elements_count; \
	} while(0)

#define array_add_many_at(array, elements, elements_count, pos) \
	do { \
		if(!(array)) array_create((array)); \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		while(h->len - h->count < elements_count) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		memmove((array) + (pos) + elements_count, (array) + (pos), (h->count - (pos)) * sizeof(*(array))); \
		memmove((array) + (pos), (elements), elements_count * sizeof(*(array))); \
		h->count += elements_count; \
	} while(0)

#define array_update(array, update, pos) array_input_unsafe((array), (update), (pos))

#define array_copy(array, new_array) \
	do { \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		array_add_many((new_array), (array), h->count); \
	} while(0)

#define array_concat(array1, array2) \
	do { \
		ArrayHeader *h2 = ((ArrayHeader*)(array2)) - 1; \
		array_add_many((array1), (array2), h2->count); \
	} while(0)

#define array_concat_new(array1, array2, arrayret) \
	do { \
		if(!(arrayret)) array_create((arrayret)); \
		ArrayHeader *h1 = ((ArrayHeader*)(array1)) - 1; \
		ArrayHeader *h2 = ((ArrayHeader*)(array2)) - 1; \
		array_add_many((arrayret), (array1), h1->count); \
		array_add_many((arrayret), (array2), h2->count); \
	} while(0)

//pos is a return argument
#define array_has(array, val, pos) \
	({ \
	 	bool found = false; \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		for(size_t i = 0; i < h->count; i++) { \
			if((array)[i] == (val)) { \
				*(pos) = i; \
	 			found = true; \
			} \
			if(found) break; \
		} \
		found; \
	})

#define array_has_at(array, val, pos) (array)[(pos)] == (val) //wont work with custom struct pointers

#define array_size(array) (((ArrayHeader*)(array)) - 1)->count

#define array_is_empty(array) (array_size((array)) == 0)

#define array_sort(array) HEEEELP

#define array_remove_at(array, pos, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if(out_ptr) *out_ptr = (array)[(pos)]; \
		memmove((array) + (pos), (array) + (pos) + 1, sizeof(*(array)) * (h->count - (pos) - 1)); \
		h->count -= 1; \
	} while(0)

//changes array order
#define array_remove_at_fast(array, pos, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if(out_ptr) *out_ptr = (array)[(pos)]; \
		(array)[(pos)] = (array)[h->count - 1]; \
		h->count -= 1; \
	} while(0)

#define array_pop(array, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if(out_ptr) *out_ptr = (array)[h->count - 1]; \
		h->count -= 1; \
	} while(0)

#define array_remove_first(array, out_ptr) array_remove_at(array, 0, out_ptr)

#define array_remove_val(array, val) \
	({ \
	 	bool deleted = false; \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		for(size_t i = 0; i < h->count; i++) { \
			if((array)[i] == val) { \
	 			array_remove_at((array), i, NULL); \
				deleted = true; \
			} \
		} \
		deleted; \
	})

#define array_clear(array) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		for(size_t i = 0; i < h->count; i++) { \
			(array)[i] = 0; \
		} \
		h->count = 0; \
	} while(0)

#define array_destroy(array) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		free(h); \
		(array) = NULL; \
	} while(0)

ArrayList *al_alloc() {
    ArrayList *list = calloc(1, sizeof(*list));
    return list;
}

ArrayList *al_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
    ArrayList *list = al_alloc();
    if(!list) return NULL;
    list->elements = calloc(256, size_elements);
    if(!(list->elements)) {
        free(list);
        return NULL;
    }
    list->len = 256;
    list->size_elements = size_elements;
	if(compare_function) list->compare_function = compare_function;
	else list->compare_function = &memcmp;
	list->destroy_function = destroy_function;
    return list;
}

ArrayList *al_create_sized(size_t size_elements, size_t len, compare_fn compare_function, destroy_fn destroy_function) {
    ArrayList *list = al_alloc();
    if(!list) return NULL;
    list->elements = calloc(len, size_elements);
    if(!(list->elements)) {
        free(list);
        return NULL;
    }
    list->len = len;
    list->size_elements = size_elements;
	if(compare_function) list->compare_function = compare_function;
	else list->compare_function = &memcmp;
	list->destroy_function = destroy_function;
    return list;
}

bool al_realloc(ArrayList *list) {
    if(!list) return false;
	if(list->len == 0) return false;
	if(list->size_elements > SIZE_MAX / list->len / 2) return false;
    void *check = realloc(list->elements, list->size_elements * list->len * 2);
    if(!check) return false;
    list->elements = check;
    list->len *= 2;
    return true;
}

//This function does not increment list count
bool al_input_unsafe(ArrayList *list, void *new_element, size_t position) {
    if(!list || !new_element) return false;
    if(position >= list->len) return false;
    
    uint8_t *dest = (uint8_t *)list->elements + (list->size_elements * position);
    memmove(dest, (uint8_t *)new_element, list->size_elements);
    return true;
}

bool al_add(ArrayList *list, void *new_element) {
    if(!list || !new_element) return false;
    if(list->count == list->len)
        if(!al_realloc(list)) return false;
    
    uint8_t *dest = (uint8_t *)list->elements + (list->size_elements * list->count);
    memmove(dest, new_element, list->size_elements);
    list->count += 1;
    return true;
}

bool al_push(ArrayList *list, void *new_element) {
	return al_add(list, new_element);
}

bool al_add_at(ArrayList *list, void *new_element, size_t pos) {
    if(!list || !new_element) return false;
	if(list->count == list->len)
        if(!al_realloc(list)) return false;
    if(list->count <= pos) return al_add(list, new_element);
	memmove((uint8_t*)list->elements + (list->size_elements * (pos + 1)),
			(uint8_t*)list->elements + (list->size_elements * pos),
			list->size_elements * (list->count - pos));
    memmove((uint8_t*)list->elements + (list->size_elements * pos), new_element, list->size_elements);
    list->count += 1;
    return true;
}

bool al_add_many(ArrayList *list, void *elements, size_t elements_count) {
    if(!list || !elements) return false;
    if(list->count + elements_count >= list->len) {
        while(list->len < list->count + elements_count) {
			if(!al_realloc(list)) return false;
        }
    }
	memmove((uint8_t*)list->elements + (list->count * list->size_elements),
			elements,
			list->size_elements * elements_count);
	list->count += elements_count;
    return true;
}

bool al_add_many_at(ArrayList *list, void *elements, size_t elements_count, size_t pos) {
	if(!list || !elements) return false;
	if(list->count <= pos) return al_add_many(list, elements, elements_count);
	if(list->count + elements_count >= list->len) {
        while(list->len < list->count + elements_count) {
            void *check = realloc(list->elements, list->size_elements * list->len * 2);
            if(!check) return false;
            list->elements = check;
            list->len *= 2;
        }
	}
	memmove((uint8_t*)list->elements + ((pos + elements_count) * list->size_elements),
			(uint8_t*)list->elements + (pos * list->size_elements),
			list->size_elements * elements_count);
	memmove((uint8_t*)list->elements + (pos * list->size_elements),
			elements,
			list->size_elements * elements_count);
	list->count += elements_count;
	return true;
}

bool al_update(ArrayList *list, void *update, size_t pos) {
	return al_input_unsafe(list, update, pos);
}

ArrayList *al_copy_list(ArrayList *list) {
    if(!list) return NULL;
    ArrayList *cpy = al_create_sized(list->size_elements, list->len, list->compare_function, list->destroy_function);
	memmove(cpy->elements, list->elements, list->count * list->size_elements);
	cpy->count = list->count;
    return cpy;
}

void al_concat_list(ArrayList *l1, ArrayList *l2) {
	if(!l1 || !l2) return;
	if(l1->size_elements != l2->size_elements) return;
	al_add_many(l1, l2->elements, l2->count);
}

ArrayList *al_concat_list_new(ArrayList *l1, ArrayList *l2) {
    if(!l1 || !l2) return NULL;
    if(l1->size_elements != l2->size_elements) return NULL;
    ArrayList *lret = al_alloc();
    if(!lret) return NULL;
    uint64_t n_size = l1->count + l2->count;
    uint64_t i = 1;
    for(i; i < n_size; i *= 2);
    if(i < 256) i = 256;
    uint8_t *a = calloc(i, l1->size_elements);
    if(!a) {
        free(lret);
        return NULL;
    }
    memmove(a, l1->elements, l1->count * l1->size_elements);
    memmove(a + (l1->count * l1->size_elements), (uint8_t *)l2->elements, l2->count * l2->size_elements);

    lret->elements = (void *)a;
    lret->size_elements = l1->size_elements;
    lret->count = n_size;
    lret->len = i;
    return lret;
}

size_t al_size(ArrayList *list) {
	return list->count;
}

bool al_is_empty(ArrayList *list) {
    return !list || list->count == 0;
}

bool al_has(ArrayList *list, void *val, size_t *pos) {
    if(!list || !val) return false;
    for(size_t i = 0; i < list->count; i++) {
        bool found = true;
        uint8_t *s1 = (uint8_t *)list->elements + (i * list->size_elements);
        if(list->compare_function(s1, val, list->size_elements) != 0) 
            found = false;
        if(found) {
            *pos = i;
            return true;
        }
    }
    return false;
}

bool al_has_at(ArrayList *list, void *val, size_t pos) {
    if(!list || !val) return false;
    if(list->count <= pos) return false;
    bool found = true;
    uint8_t *s1 = (uint8_t *)list->elements + (pos * list->size_elements);
    if(list->compare_function(s1, val, list->size_elements) != 0) found = false;
    return found;
}

void *al_get_ith(ArrayList *list, size_t i) {
    if(!list || i >= list->count) return NULL;
    return (uint8_t *)list->elements + (list->size_elements * i);
}

bool al_sort(ArrayList *list) {
	//TODO:
}

void al_iterate(ArrayList *list, iter_fn func, void *arg) {
	if(!list || !func) return;
	for(size_t i = 0; i < list->count; i++) {
		void *element = (uint8_t*)list->elements + (i * list->size_elements);
		func(element, arg);
	}
}

bool al_remove_at(ArrayList *list, size_t pos, void *out_ptr) {
    if(!list) return false;
    if(list->count == 0 || list->count <= pos) return false;
    void *src = (uint8_t*)list->elements + (list->size_elements * pos);
    if(out_ptr) memmove(out_ptr, src, list->size_elements);
	//FIXME: for EVERY remove in the project, there can be memory leak if destroy_function is not used in member
    memmove(src,
            (uint8_t *)src + list->size_elements,
            list->size_elements * (list->count - pos - 1));
    list->count -= 1;
    return true;
}

bool al_remove_at_fast(ArrayList *list, size_t pos, void *out_ptr) {
	if(!list) return false;
	if(list->count == 0 || list->count <= pos) return false;
	void *src = (uint8_t*)list->elements + (list->size_elements * pos);
	if(out_ptr) memmove(out_ptr, src, list->size_elements);
	memmove(src,
			(uint8_t*)list->elements + (list->size_elements * (list->count - 1)),
			list->size_elements);
	list->count -= 1;
	return true;
}

bool al_pop(ArrayList *list, void *out_ptr) {
    return al_remove_at(list, list->count - 1, out_ptr);
}

bool al_remove_first(ArrayList *list, void *out_ptr) {
    return al_remove_at(list, 0, out_ptr);
}

bool al_remove_val(ArrayList *list, void *val) {
    if(!list) return false;
    if(!val) return false;
    size_t pos = 0;
    if(al_has(list, val, &pos)) {
        return al_remove_at(list, pos, 0);;
    }
    return false;
}

bool al_clear(ArrayList *list) {
	if(!list) return false;
	memset(list->elements, 0, list->size_elements * list->count);
	list->count = 0;
	return true;
}

void _destroy_iter(void *element, void *arg) {
	pointer_destroy(element);
}

bool al_destroy(ArrayList **list) {
    if(!list) return false;
    if(!*list) return false;
	if((*list)->destroy_function) al_iterate(*list, &_destroy_iter, NULL);
    free((*list)->elements);
    (*list)->elements = NULL;
    (*list)->len = 0;
    (*list)->size_elements = 0;
    free(*list);
    *list = NULL;
    return true;
}

LinkedList *ll_alloc() {
    LinkedList *list = calloc(1, sizeof(*list));
    return list;
}

LinkedList *ll_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
    LinkedList *list = ll_alloc();
    if(!list) return NULL;
    list->size_elements = size_elements;
	if(compare_function) list->compare_function = compare_function;
	else list->compare_function = &memcmp;
	list->destroy_function = destroy_function;
    return list;
}

LLNode *ll_create_node(void *val, size_t size_elements) {
    if(!val) return NULL;
    LLNode *node = calloc(1, sizeof(*node));
    if(!node) return NULL;
    node->before = NULL;
    node->next = NULL;
    node->element = malloc(size_elements);
    if(!node->element) {
        free(node);
        return NULL;
    }
    memmove((uint8_t *)node->element, (uint8_t *)val, size_elements);
    return node;
}

bool ll_add_tail(LinkedList *list, void *val) {
    if(!list || !val) return false;
    if(!list->head) {
        list->head = ll_create_node(val, list->size_elements);
        if(!list->head) return NULL;
        list->head->before = list->head;
        list->head->next = list->head;
        list->tail = list->head;
        list->count += 1;
        return true;
    }
    list->tail->next = ll_create_node(val, list->size_elements);
    if(!list->tail->next) return NULL;
    LLNode *p = list->tail->next;
    p->before = list->tail;
    list->tail = p;
    list->tail->next = list->head;
    list->head->before = list->tail;
    list->count += 1;
    return true;
}

bool ll_add_head(LinkedList *list, void *val) {
    if(!list || !val) return false;
    if(!list->head) {
        list->head = ll_create_node(val, list->size_elements);
        if(!list->head) return NULL;
		list->head->next = list->head;
		list->head->before = list->head;
        list->tail = list->head;
        list->count += 1;
        return true;
    }
    LLNode *p = ll_create_node(val, list->size_elements);
    if(!p) return NULL;
    p->next = list->head;
    list->head->before = p;
    list->head = p;
    list->head->before = list->tail;
    list->tail->next = list->head;
    list->count += 1;
    return true;
}

bool ll_add_at(LinkedList *list, void *val, size_t pos) {
	if(!list || !val) return false;
	if(pos == 0) return ll_add_head(list, val);
	if(pos == list->count - 1) return ll_add_tail(list, val);
	size_t i = 0;
	LLNode *p = list->head;
	do {
		if(i == pos) break;
		p = p->next;
		i++;
	} while(p != list->head);
	LLNode *new = ll_create_node(val, list->size_elements);
	if(!new) return false;
	p->before->next = new;
	new->before = p->before->next;
	new->next = p;
	p->before = new;
	list->count += 1;
	return true;
}

bool ll_add_many_at(LinkedList *list, void *elements, size_t elements_count, size_t pos) {
	if(!list || !elements) return false;
	LLNode *first = ll_create_node(elements, list->size_elements);
	LLNode *last = first;
	for(size_t i = 1; i < elements_count; i++) {
		last->next = ll_create_node((uint8_t*)elements + (i * list->size_elements), list->size_elements);
		last->next->before = last;
		last = last->next;
	}
	LLNode *node_at_pos = ll_get_node_at(list, pos);
	if(!node_at_pos) {
		list->head = first;
		list->tail = last;
		list->tail->next = list->head;
		list->head->before = list->tail;
		return true;
	}
	node_at_pos->before->next = first;
	first->before = node_at_pos->before;
	node_at_pos->before = last;
	last->next = node_at_pos;

	if(pos == 0) list->head = first;
	if(pos >= list->count) list->tail = last;
	list->count += elements_count;
	return true;
}

bool ll_add_many(LinkedList *list, void *elements, size_t elements_count) {
	if(!list || !elements) return false;
	return ll_add_many_at(list, elements, elements_count, list->count);
}

LinkedList *ll_copy_list(LinkedList *list) {
	if(!list) return NULL;
	LinkedList *new_l = ll_create(list->size_elements, list->compare_function, list->destroy_function);
	if(!new_l) return NULL;
	LLNode *p = list->head;
	for(size_t i = 0; i < list->count; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_add_tail(new_l, p->element);
		p = p->next;
	}
	return new_l;
}

void ll_concat_list(LinkedList *list1, LinkedList *list2) {
	if(!list1 || !list2) return;
	if(list1->size_elements != list2->size_elements) return;
	LLNode *p = list2->head;
	for(size_t i = 0; i < list2->count; i++) {
		ll_add_tail(list1, p->element);
		p = p->next;
	}
}

LinkedList *ll_concat_list_new(LinkedList *list1, LinkedList *list2) {
	if(!list1 || !list2) return NULL;
	LinkedList *new_l = ll_create(list1->size_elements, list1->compare_function, list1->destroy_function);
	if(!new_l) return NULL;
	LLNode *p = list1->head;
	for(size_t i = 0; i < list1->count; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_add_tail(new_l, p->element);
		p = p->next;
	}
	p = list2->head;
	for(size_t i = 0; i < list2->count; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_add_tail(new_l, p->element);
		p = p->next;
	}
	return new_l;
}

void ll_iterate(LinkedList *list, iter_fn func, void *arg) {
	if(!list || !func) return;
	LLNode *p = list->head;
	for(size_t i = 0; i < list->count; i++) {
		void *element = p->element;
		func(element, arg);
		p = p->next;
	}
}

bool ll_remove_tail(LinkedList *list, void *out_ptr) {
    if(!list) return false;
    if(!list->head) return false;
    if(list->head == list->tail) {
        LLNode *head = list->head;
		if(out_ptr) memmove(out_ptr, head->element, list->size_elements);
		free(head->element);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->count--;
        return true;
    }
    LLNode *tail = list->tail;
    tail->before->next = list->head;
    list->head->before = tail->before;
    list->tail = tail->before;
	if(out_ptr) memmove(out_ptr, tail->element, list->size_elements);
	free(tail->element);
    free(tail);
    list->count--;
    return true;
}

bool ll_remove_head(LinkedList *list, void *out_ptr) {
    if(!list) return false;
    if(!list->head) return false;
    if(list->head == list->tail) {
        LLNode *head = list->head;
		if(out_ptr) memmove(out_ptr, head->element, list->size_elements);
		free(head->element);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->count--;
        return true;
    }
    LLNode *head = list->head;
    head->next->before = list->tail;
    list->tail->next = head->next;
    list->head = head->next;
	if(out_ptr) memmove(out_ptr, head->element, list->size_elements);
	free(head->element);
    free(head);
    list->count--;
    return true;
}

bool ll_remove_val(LinkedList *list, void *val) {
	if(!list || !val) return false;
    LLNode *p = ll_get_node(list, val);
    if(!p) return false;
    if(p == list->head && p == list->tail) {
        void *val = p->element;
        list->head = NULL;
        list->tail = NULL;
		free(val);
        free(p);
        return true;
    }
    LLNode *before = p->before;
    LLNode *next = p->next;
    before->next = next;
    next->before = before;
    if(p == list->head)
        list->head = next;
    if(p == list->tail)
        list->tail = before;
	free(p->element);
    free(p);
    list->count--;
    return true;
}

bool ll_remove_at(LinkedList *list, size_t pos, void *out_ptr) {
    if(!list) return false;
    if(!list->head) return false;
    LLNode *p = list->head;
    for(size_t i = 0; i < pos; i++)
        p = p->next;
    if(p == list->head && p == list->tail) {
        void *val = p->element;
        list->head = NULL;
        list->tail = NULL;
		if(out_ptr) memmove(out_ptr, val, list->size_elements);
		free(val);
        free(p);
        return true;
    }
    LLNode *before = p->before;
    LLNode *next = p->next;
    before->next = next;
    next->before = before;
    if(p == list->head)
        list->head = next;
    if(p == list->tail)
        list->tail = before;
	if(out_ptr) memmove(out_ptr, p->element, list->size_elements);
	free(p->element);
    free(p);
    list->count--;
    return true;
}

LLNode *ll_get_node(LinkedList *list, void *val) {
    if(!list || !val) return NULL;
    if(!list->head) return NULL;
    LLNode *p = list->head;
    do {
        if(list->compare_function((uint8_t *)p->element, (uint8_t *)val, list->size_elements) == 0) return p;
        p = p->next;
    } while(p != list->head);
    return NULL;
}

LLNode *ll_get_node_at(LinkedList *list, size_t pos) {
    if(pos == 0) return list->head;
    if(pos == list->count - 1) return list->tail;
    LLNode *p = list->head;
    for(size_t i = 0; i < pos; i++)
        p = p->next;
    return p;
}

void ll_destroy(LinkedList **list) {
    if(!list) return;
    if(!*list) return;
    if(!(*list)->head) {
        free(*list);
        *list = NULL;
        return;
    }
    LLNode *head = (*list)->head;
    LLNode *p = head;
    do {
		if((*list)->destroy_function) (*list)->destroy_function(p->element);
        free(p->element);
        LLNode *next = p->next;
        free(p);
        p = next;
    } while(p != head);
    free(*list);
    *list = NULL;
}

HashSet *hs_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
    HashSet *hs = malloc(sizeof(*hs));
    if(!hs) return NULL;
    hs->list = al_create(sizeof(HashEntry), NULL, NULL);
    if(!hs->list) {
        free(hs);
        return NULL;
    }
    for(size_t i = 0; i < hs->list->count; i++) {
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
    return hs_hash_function(val, size_element) % hs->list->count;
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
        ith->element = ll_create(hs->size_elements, hs->compare_function, hs->destroy_function);
    return ll_add_tail(ith->element, val);
}

bool hs_rehash(HashSet *hs) {
    if(!hs) return false;
    ArrayList *new = al_create_sized(sizeof(HashEntry), hs->list->count * 2, NULL, NULL);
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
                new_entry->element = ll_create(hs->size_elements, hs->compare_function, hs->destroy_function);
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

HashMapPair *_hmp_create(void *key, void *value, size_t size_key, size_t size_value) {
	HashMapPair *hmp = malloc(sizeof(*hmp));
	if(!hmp) return NULL;
	hmp->key = malloc(size_key);
	hmp->value = malloc(size_value);
	if(!(hmp->key) || !(hmp->value)) {
		free(hmp);
		if(hmp->key) free(hmp->key);
		if(hmp->value) free(hmp->value);
		return NULL;
	}
	memcpy(hmp->key, key, size_key);
	memcpy(hmp->value, value, size_value);
	return hmp;
}

HashMap *hm_create(size_t size_key, size_t size_value, compare_fn compare_key, compare_fn compare_value, destroy_fn destroy_key, destroy_fn destroy_value) {
	HashMap *hm = malloc(sizeof(*hm));
	if(!hm) return NULL;
	hm->hs = hs_create(sizeof(HashMapPair), NULL, NULL);
	if(!(hm->hs)) {
		free(hm);
		return NULL;
	}
	hm->size_key = size_key;
	hm->size_value = size_value;
	
	if(compare_key) hm->compare_key = compare_key;
	else hm->compare_key = &memcmp;
	if(compare_value) hm->compare_value = compare_value;
	else hm->compare_value = &memcmp;
	hm->destroy_key = destroy_key;
	hm->destroy_value = destroy_value;
	return hm;
}

bool hm_add(HashMap *hm, void *key, void *value) {
	if(!hm || !key || !value) return false;
	if(hm_has_key(hm, key)) return false;
	HashMapPair *new_entry = _hmp_create(key, value, hm->size_key, hm->size_value);
	if(!new_entry) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
	if(hs_add_val(hm->hs, new_entry, hs_hash_val(hm->hs, key, hm->size_key))) hm->hs->count++;
	if(hs_load_factor(hm->hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hm->hs);
	return true;
}

bool hm_has_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
    HashEntry*ith = (HashEntry*)al_get_ith(hm->hs->list, pos);
	if(!(ith->valid_entry)) return false;
	if(!(ith->element)) return false;
	LinkedList *ll = ith->element;
	LLNode *head = ll->head;
	if(!head) return false;
	LLNode *p = head;
	int res = 0;
	do {
		HashMapPair *hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->size_key);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return true;
	return false;
}

bool hm_has_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	bool found = false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->count; i++) {
		HashEntry entry = ((HashEntry*)(list->elements))[i];
		if(entry.valid_entry == false) continue;
		if(entry.element == NULL) continue;
		LinkedList *ll = entry.element;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		int res = 0;
		do {
			HashMapPair *hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->size_value);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) found = true;
		if(found) break;
	}
	return found;
}

void*hm_get_value(HashMap *hm, void *key) {
	if(!hm || !key) return NULL;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
    HashEntry*ith = (HashEntry*)al_get_ith(hm->hs->list, pos);
	if(!(ith->valid_entry)) return NULL;
	if(!(ith->element)) return NULL;
	LinkedList *ll = ith->element;
	LLNode *head = ll->head;
	if(!head) return NULL;
	LLNode *p = head;
	HashMapPair *hmp;
	int res = 0;
	do {
		hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->size_key);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return hmp->value;
	return NULL;
}

void*hm_get_key(HashMap *hm, void *value) {
	if(!hm || !value) return NULL;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->count; i++) {
		HashEntry entry = ((HashEntry*)(list->elements))[i];
		if(entry.valid_entry == false) continue;
		if(entry.element == NULL) continue;
		LinkedList *ll = entry.element;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		int res = 0;
		do {
			hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->size_value);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) return hmp->key;
	}
	return NULL;
}

bool hm_remove_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
    HashEntry*ith = (HashEntry*)al_get_ith(hm->hs->list, pos);
	if(!(ith->valid_entry)) return false;
	if(!(ith->element)) return false;
	LinkedList *ll = ith->element;
	LLNode *head = ll->head;
	if(!head) return false;
	LLNode *p = head;
	HashMapPair *hmp;
	int res = 0;
	do {
		hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->size_key);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) {
		return ll_remove_val(ll, hmp);
	}
	return false;
}

bool hm_remove_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->count; i++) {
		HashEntry entry = ((HashEntry*)(list->elements))[i];
		if(entry.valid_entry == false) continue;
		if(entry.element == NULL) continue;
		LinkedList *ll = entry.element;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		int res = 0;
		do {
			hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->size_value);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) {
			return ll_remove_val(ll, hmp);
		}
	}
	return false;
}

bool hm_is_empty(HashMap *hm) {
	return hm_size(hm) == 0;
}

size_t hm_size(HashMap *hm) {
	if(!hm) return 0;
	return hm->hs->count;
}

size_t hm_struct_size(HashMap *hm) {
	if(!hm) return 0;
	ArrayList *list = hm->hs->list;
	size_t total = 0;
	size_t structs = sizeof(HashMap) + sizeof(HashSet) + sizeof(ArrayList);
	size_t counting = (list->count * sizeof(HashEntry)) + (hm->hs->count * (sizeof(HashMapPair) + hm->size_key + hm->size_value));
	for(size_t i = 0; i < list->count; i++) {
		HashEntry ith = ((HashEntry*)(list->elements))[i];
		if(ith.valid_entry == false) continue;
		if(ith.element == NULL) continue;
		structs += sizeof(LinkedList);
		LinkedList *ll = ith.element;
		LLNode *head = ll->head;
		LLNode *p = head;
		do {
			structs += sizeof(LLNode);
			p = p->next;
		} while(p != head);
	}
	total += structs + counting;
	if(total < counting || total < structs) return ~((size_t)0);//size_t max
	return total;
}

bool hm_destroy(HashMap **hm) {
	if(!hm || !*hm) return false;
	for(size_t i = 0; i < (*hm)->hs->list->count; i++) {
		HashEntry ith = ((HashEntry*)((*hm)->hs->list->elements))[i];
		if(ith.valid_entry == false) continue;
		if(ith.element == NULL) continue;
		LinkedList *ll = ith.element;
		LLNode *p = ll->head;
		do {
			(*hm)->destroy_key(((HashMapPair*)(p->element))->key);
			(*hm)->destroy_value(((HashMapPair*)(p->element))->value);
		} while(p != ll->head);
	}
	if(!hs_destroy(&((*hm)->hs))) return false;
	free(*hm);
	*hm = NULL;
	return true;
}

#define bt_insert_const(bst, val, type) \
	do {\
		type var = (val);\
		bt_insert((bst), &var);\
	} while(0)

#define bt_remove_const(bst, val, type) \
	do {\
		type var = (val);\
		bt_remove((bst), &var);\
	} while(0)

int64_t _bt_max_impl(int64_t a, int64_t b) {
	return a > b ? a : b;
}

BinaryTreeNode *bt_create_node(void *val, size_t size_elements) {
    BinaryTreeNode *n = malloc(sizeof(*n));
	if(!n)
		return NULL;
    n->element = malloc(size_elements);
	if(!(n->element)) {
		free(n);
		return NULL;
	}
    memcpy(n->element, val, size_elements);
	n->left = NULL;
	n->right = NULL;
	n->height = 0;
	return n;
}

BinaryTree *bt_create(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
	BinaryTree *bst = malloc(sizeof(*bst));
	if(!bst) return NULL;
	bst->root = NULL;
	bst->size_elements = size_elements;
	if(compare_function) bst->compare_function = compare_function;
	else bst->compare_function = &memcmp;
	bst->destroy_function = destroy_function;
	return bst;
}

int64_t bt_height(BinaryTreeNode *root) {
	if(!root) return -1;
	return root->height;
}

void bt_update_height(BinaryTreeNode *root) {
	root->height =_bt_max_impl(bt_height(root->left), bt_height(root->right)) + 1;
}

int64_t bt_balance(BinaryTreeNode *root) {
	if(!root) return 0;
	return bt_height(root->left) - bt_height(root->right);
}

bool bt_is_balanced(BinaryTreeNode *root) {
	int64_t balance_factor = bt_balance(root);
	return !(balance_factor < -1 || balance_factor > 1);
}

BinaryTreeNode *_bt_rotate_left(BinaryTreeNode*root) {
	if(!root) return NULL;
	if(!(root->right)) return NULL;
	BinaryTreeNode *right = root->right;
	BinaryTreeNode *rl = right->left;

	right->left = root;
	root->right = rl;

	bt_update_height(root);
	bt_update_height(right);

	return right;
}

BinaryTreeNode *_bt_rotate_right(BinaryTreeNode*root) {
	if(!root) return NULL;
	if(!(root->left)) return NULL;
	BinaryTreeNode *left = root->left;
	BinaryTreeNode *lr = left->right;

	left->right = root;
	root->left = lr;

	bt_update_height(root);
	bt_update_height(left);

	return left;
}

BinaryTreeNode *_bt_rebalance(BinaryTreeNode*root) {
	int64_t factor = bt_balance(root);

	if(factor > 1) {
		if(bt_balance(root->left) < 0)
			root->left = _bt_rotate_left(root->left);
		return _bt_rotate_right(root);
	}
	if(factor < -1) {
		if(bt_balance(root->right) > 0)
			root->right = _bt_rotate_right(root->right);
    	return _bt_rotate_left(root);
	}

	return root;
}

BinaryTreeNode *_bt_insert_internal(BinaryTree *root, BinaryTreeNode *node, void *val) {
	if(!root || !val) return NULL;
	if(!node) return bt_create_node(val, root->size_elements);
    int res = root->compare_function(node->element, val, root->size_elements);
	if(res < 0) {
		BinaryTreeNode *temp = _bt_insert_internal(root, node->right, val);
		if(temp) node->right = temp;
	}
    else if(res > 0) {
		BinaryTreeNode *temp = _bt_insert_internal(root, node->left, val);
		if(temp) node->left = temp;
	}
	else
		return node;

	bt_update_height(node);
	return _bt_rebalance(node);
}

bool bt_insert(BinaryTree *root, void *val) {
	if(!root || !val) return false;

	root->root = _bt_insert_internal(root, root->root, val);

    return true;
}

BinaryTreeNode *_bt_remove_internal(BinaryTree *root, BinaryTreeNode *node, void *val) {
    if(!root || !node || !val) return NULL;
	int res = root->compare_function(node->element, val, root->size_elements);
    if(res == 0) {
        if(!(node->left) || !(node->right)) {
			BinaryTreeNode *aux = node->left ? node->left : node->right;
			if(aux) {
				BinaryTreeNode *to_free = node;
				node = aux;
				to_free->left = NULL;
				to_free->right = NULL;
				bt_delete_node(to_free, root->destroy_function);
				return node;
			}
			aux = node;
			node = NULL;
			bt_delete_node(aux, root->destroy_function);
        }
		else {
			BinaryTreeNode *aux = node->left;
			while(aux->right)
				aux = aux->right;
			void *temp = node->element;
			node->element = aux->element;
			aux->element = temp;
			node->left = _bt_remove_internal(root, node->left, aux->element);
		}
    }
	else if(res > 0)
        node->left = _bt_remove_internal(root, node->left, val);
	else if(res < 0)
        node->right = _bt_remove_internal(root, node->right, val);

	if(!node) return NULL;
	
	bt_update_height(node);
	return _bt_rebalance(node);
}

bool bt_remove(BinaryTree *root, void *val) {
    if(!root|| !(root->root) || !val) return false;
	root->root = _bt_remove_internal(root, root->root, val);
	return true;
}

BinaryTreeNode *_bt_search_internal(BinaryTree *root, BinaryTreeNode *node, void *val) {
	if(!root || !node || !val) return NULL;
    int res = root->compare_function(node->element, val, root->size_elements);
	if(res == 0)
        return node;
    if(res > 0) {
        node = node->left;
        return _bt_search_internal(root, node, val);
    }
    else {
        node = node->right;
        return _bt_search_internal(root, node, val);
    }
    return NULL;
}

BinaryTreeNode *bt_search(BinaryTree *root, void *val){
    if (!root || !val) return NULL;
	
	return _bt_search_internal(root, root->root, val);
}

// BinaryTreeNode *bt_invert_tree(BinaryTreeNode *root) {
//     if (!root) return 0;
//
//     BinaryTreeNode *helper;
//     helper = root->left;
//     root->left = root->right;
//     root->right = helper;
//
//     bt_invert_tree(root->left);
//     bt_invert_tree(root->right);
//
//     return root;
// }

int _bt_display_tree(char ** buffer, BinaryTreeNode *no, int level, double h_position, int cols){
	char * ptr;
	int i, col, a, b;
	double offset;
	
	if(!no) return level;
	col = (int)(h_position * cols);
	offset = 1.0 / pow(2, level + 2);

	ptr = buffer[1 + level * 3] + col;
	sprintf(ptr, "%03d", *(int*)no->element);
	*(ptr + strlen(ptr)) = ' ';

	if(no->left || no->right)
		*(buffer[2 + level * 3] + col + 1) = '|';

	if(no->left){
		i = (int)((h_position - offset) * cols);
		*(buffer[3 + level * 3] + 1 + i) = '|';
		i++;
		for(; i <= col; i++)
			*(buffer[3 + level * 3] + 1 + i) = '-';
	}
	
	if(no->right){
		for(i = col; i < (int)((h_position + offset) * cols); i++)
			*(buffer[3 + level * 3] + 1 + i) = '-';
		*(buffer[3 + level * 3] + 1 + i) = '|';
	}

	a = _bt_display_tree(buffer, no->left, level + 1, h_position - offset, cols);
	b = _bt_display_tree(buffer, no->right, level + 1, h_position + offset, cols);

	if(a > b)
		return a;
	return b;
}

void _bt_print_internal(BinaryTreeNode *no, int rows, int cols){
	int i, j, r;
	char ** buffer = (char **) malloc(rows * sizeof(char *));
	for(i = 0; i < rows; i++) {
		buffer[i] = (char *) malloc((cols + 1) * sizeof(char));
		for(j = 0; j < cols; j++)
			buffer[i][j] = ' ';
		buffer[i][j] = '\0';
	}
	r = _bt_display_tree(buffer, no, 0, 0.5, cols);
	for(i = 0; i < 3 * r; i++)
		printf("%s\n", buffer[i]);
}

void bt_print(BinaryTree *root, int rows, int cols) {
	_bt_print_internal(root->root, rows, cols);
}

void bt_delete_node(BinaryTreeNode *node, destroy_fn destroy_function) {
	if(!node) return;
	bt_delete_node(node->left, destroy_function);
	bt_delete_node(node->right, destroy_function);
	if(destroy_function) destroy_function(node->element);
	free(node->element);
	free(node);
}

void bt_delete(BinaryTree **root) {
	if(!root || !(*root)) return;
	bt_delete_node((*root)->root, (*root)->destroy_function);
	free(*root);
	*root = NULL;
}

AbstractTree *at_create(void *val, size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
    AbstractTree* node = malloc(sizeof(*node));
    if(!node) return NULL;
	node->element = malloc(size_elements);
	if(!node->element) {
		free(node);
		return NULL;
	}
	memcpy(node->element, val, size_elements);
    node->size_elements = size_elements;
    node->child = NULL;
    node->sibling = NULL;
	node->compare_function = compare_function;
	node->destroy_function = destroy_function;
    return node;
}

void at_add_child(AbstractTree* parent, AbstractTree* child) {
    if(parent->child == NULL) {
        parent->child = child;
    } else {
        AbstractTree* sibling = parent->child;
        while(sibling->sibling != NULL) 
            sibling = sibling->sibling;
        sibling->sibling = child;
    }
}

void _at_print_tree_rec(AbstractTree* root, int level) {
    for(int i = 0; i < level; i++) {
        if(i==level-1)
            printf("─");
        else 
            printf("└");
    }
    printf("%p\n", root->element); //TODO: add way to print accordingly
    AbstractTree* child = root->child;
    while(child != NULL) {
        _at_print_tree_rec(child, level + 1);
        child = child->sibling;
    }
}

void at_print_tree(AbstractTree *root) {
    _at_print_tree_rec(root, 0);
}

bool at_destroy(AbstractTree **root) {
	if(!*root) return false;
	at_destroy(&((*root)->child));
	at_destroy(&((*root)->sibling));
	if((*root)->destroy_function)
		(*root)->destroy_function((*root)->element);
	free((*root)->element);
	free(*root);
	*root = NULL;
	return true;
}

#endif //STRCTS_IMPLEMENTATION

