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
ArrayList *al_create(size_t size_elements);
ArrayList *al_create_sized(size_t size_elements, size_t len);
ArrayList *al_create_comparator(size_t size_elements, compare_fn compare_function);
ArrayList *al_create_destroyer(size_t size_elements, destroy_fn destroy_function);
ArrayList *al_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void       al_change_comparator(ArrayList *list, compare_fn compare_function);
void       al_change_destroyer(ArrayList *list, destroy_fn destroy_function);
bool       al_realloc(ArrayList *list);
bool al_input_unsafe(ArrayList *list, void *new_element, size_t position);
bool al_insert(ArrayList *list, void *new_element);
bool al_add(ArrayList *list, void *new_element);
bool al_push(ArrayList *list, void *new_element);
bool al_add_at(ArrayList *list, void *new_element, size_t pos);
bool al_add_many(ArrayList *list, void *elements, size_t elements_count);
bool al_add_many_at(ArrayList *list, void *elements, size_t elements_count, size_t pos);
bool al_update(ArrayList *list, void *update, size_t pos);
ArrayList *al_copy_list(ArrayList *list);
void       al_concat_list(ArrayList *l1, ArrayList *l2);
ArrayList *al_concat_list_new(ArrayList *l1, ArrayList *l2);
size_t al_size(ArrayList *list);
bool   al_is_empty(ArrayList *list);
bool   al_has(ArrayList *list, void *val, size_t *pos);
bool   al_has_at(ArrayList *list, void *val, size_t pos);
void  *al_get_ith(ArrayList *list, size_t i);
bool al_sort(ArrayList *list);
void al_iterate(ArrayList *list, iter_fn func, void *arg);
bool al_remove_at(ArrayList *list, size_t pos, void *out_ptr);
bool al_remove_at_fast(ArrayList *list, size_t pos, void *out_ptr); /*changes array order*/
bool al_pop(ArrayList *list, void *out_ptr);
bool al_remove_first(ArrayList *list, void *out_ptr);
bool al_remove_val(ArrayList *list, void *val);
bool al_clear(ArrayList *list);
bool al_fit(ArrayList *list);
bool al_destroy(ArrayList **list);

//LinkedList functions
LinkedList *ll_create(size_t size_elements);
LinkedList *ll_create_comparator(size_t size_elements, compare_fn compare_function);
LinkedList *ll_create_destroyer(size_t size_elements, destroy_fn destroy_function);
LinkedList *ll_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void        ll_change_comparator(LinkedList *list, compare_fn compare_function);
void        ll_change_destroyer(LinkedList *list, destroy_fn destroy_function);
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
bool ll_destroy(LinkedList **list);

//HashSet functions
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

//HashMap functions
HashMap *hm_create(size_t size_key, size_t size_value);
HashMap *hm_create_full(size_t size_key, size_t size_value, compare_fn compare_key, compare_fn compare_value, destroy_fn destroy_key, destroy_fn destroy_value);
bool hm_add(HashMap *hm, void *key, void *value);
bool hm_has_key(HashMap *hm, void *key);
bool hm_has_value(HashMap *hm, void *value); /*O(n) search*/
void*hm_get_value(HashMap *hm, void *key); /*basically doing hm[key] <- returns the pointer to value*/
void*hm_get_key(HashMap *hm, void *value); /*O(n) search */
bool hm_remove_key(HashMap *hm, void *key); //removes pair from map by finding key
bool hm_remove_value(HashMap *hm, void *value); //removes pair from map in O(n) by value
bool   hm_is_empty(HashMap *hm);
size_t hm_size(HashMap *hm);
size_t hm_struct_size(HashMap *hm);
bool hm_destroy(HashMap **hm);

//BinaryTree functions
BinaryTreeNode *bt_create_node(void *val, size_t size_elements);
BinaryTree     *bt_create(size_t size_elements);
BinaryTree     *bt_create_comparator(size_t size_elements, compare_fn compare_function);
BinaryTree     *bt_create_destroyer(size_t size_elements, destroy_fn destroy_function);
BinaryTree     *bt_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void            bt_change_comparator(BinaryTree *tree, compare_fn compare_function);
void            bt_change_destroyer(BinaryTree *tree, destroy_fn destroy_function);
int64_t bt_height(BinaryTreeNode *root);
void    bt_update_height(BinaryTreeNode *root);
int64_t bt_balance(BinaryTreeNode *root);
bool    bt_is_balanced(BinaryTreeNode *root);
bool bt_insert(BinaryTree *tree, void *val);
bool bt_remove(BinaryTree *tree, void *val);
BinaryTreeNode *bt_search(BinaryTree *tree, void *val);
// BinaryTreeNode *bt_invert_tree(BinaryTreeNode *root);
void bt_print(BinaryTree *tree, int rows, int cols);
bool bt_destroy_node(BinaryTreeNode *node, destroy_fn destroy_function);
bool bt_destroy(BinaryTree **tree);

//AbstractTree functions
AbstractTree *at_create(void *val, size_t size_elements);
AbstractTree *at_create_full(void *val, size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void          at_change_comparator(AbstractTree *tree, compare_fn compare_function);
void          at_change_destroyer(AbstractTree *tree, destroy_fn destroy_function);
void at_add_child(AbstractTree* parent, AbstractTree* child);
void at_print_tree(AbstractTree *tree);
bool at_destroy(AbstractTree **tree);

#ifdef __cplusplus
}
#endif

//This should be a part of implementation but errors starts popping up so imma leave it here :p
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

#define array_has_at(array, val, pos) memcmp((array) + (pos), (val), sizeof(*(array))) == 0

#define array_size(array) (((ArrayHeader*)(array)) - 1)->count

#define array_is_empty(array) (array_size((array)) == 0)

#define array_remove_at(array, pos, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if((out_ptr)) *(typeof((array)))(out_ptr) = (array)[(pos)]; \
		memmove((array) + (pos), (array) + (pos) + 1, sizeof(*(array)) * (h->count - (pos) - 1)); \
		h->count -= 1; \
	} while(0)

//changes array order
#define array_remove_at_fast(array, pos, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if((out_ptr)) *(typeof((array)))(out_ptr) = (array)[(pos)]; \
		(array)[(pos)] = (array)[h->count - 1]; \
		h->count -= 1; \
	} while(0)

#define array_pop(array, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if((out_ptr)) *(typeof((array)))(out_ptr) = (array)[h->count - 1]; \
		h->count -= 1; \
	} while(0)

#define array_remove_first(array, out_ptr) array_remove_at((array), 0, (out_ptr))

#define array_remove_val(array, val) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		for(size_t i = 0; i < h->count; i++) { \
			if((array)[i] == val) { \
	 			array_remove_at((array), i, NULL); \
			} \
		} \
	} while(0)

#define array_clear(array) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		for(size_t i = 0; i < h->count; i++) { \
			(array)[i] = 0; \
		} \
		h->count = 0; \
	} while(0)

#define array_fit(array) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		h = realloc(h, sizeof(ArrayHeader) + (h->count * sizeof(*(array)))); \
		h->len = h->count; \
		(array) = (void*)(h + 1); \
	} while(0)

#define array_destroy(array) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		free(h); \
		(array) = NULL; \
	} while(0)

#define al_insert_const(list, val, type) \
	do { \
		type var = (val); \
		al_add((list), &var); \
	} while(0)

#define al_remove_const(list, val, type) \
	do { \
		type var = (val); \
		al_remove_val((list), &var); \
	} while(0)

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

ArrayList *al_alloc() {
    ArrayList *list = calloc(1, sizeof(*list));
    return list;
}

ArrayList *al_create(size_t size_elements) {
    return al_create_full(size_elements, NULL, NULL);
}

ArrayList *al_create_sized(size_t size_elements, size_t len) {
    ArrayList *list = al_alloc();
    if(!list) return NULL;
    list->elements = calloc(len, size_elements);
    if(!(list->elements)) {
        free(list);
        return NULL;
    }
    list->len = len;
    list->size_elements = size_elements;
	list->compare_function = &memcmp;
	list->destroy_function = NULL;
    return list;
}

ArrayList *al_create_comparator(size_t size_elements, compare_fn compare_function) {
	return al_create_full(size_elements, compare_function, NULL);
}

ArrayList *al_create_destroyer(size_t size_elements, destroy_fn destroy_function) {
	return al_create_full(size_elements, NULL, destroy_function);
}

ArrayList *al_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
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

void al_change_comparator(ArrayList *list, compare_fn compare_function) {
	if(!list || !compare_function) return;
	list->compare_function = compare_function;
}

void al_change_destroyer(ArrayList *list, destroy_fn destroy_function) {
	if(!list || !destroy_function) return;
	list->destroy_function = destroy_function;
}

//This function does not increment list count
bool al_input_unsafe(ArrayList *list, void *new_element, size_t position) {
    if(!list || !new_element) return false;
    if(position >= list->len) return false;
    
    uint8_t *dest = (uint8_t *)list->elements + (list->size_elements * position);
    memmove(dest, (uint8_t *)new_element, list->size_elements);
    return true;
}

bool al_insert(ArrayList *list, void *new_element) {
	return al_add(list, new_element);
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
    ArrayList *cpy = al_create_sized(list->size_elements, list->len);
	al_change_comparator(cpy, list->compare_function);
	al_change_destroyer(cpy, list->destroy_function);
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
    uint64_t i = 256;
	while(i < n_size) i *= 2;
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
	return false;
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
	if(list->destroy_function) list->destroy_function(src);
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
	if(list->destroy_function) list->destroy_function(src);
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
        return al_remove_at(list, pos, NULL);;
    }
    return false;
}

bool al_clear(ArrayList *list) {
	if(!list) return false;
	memset(list->elements, 0, list->size_elements * list->count);
	list->count = 0;
	return true;
}

bool al_fit(ArrayList *list) {
	if(!list) return false;
	list->elements = realloc(list->elements, list->count * list->size_elements);
	list->len = list->count;
	return true;
}

void _destroy_iter(void *element, void *arg) {
	ArrayList *list = arg;
	list->destroy_function(element);
}

bool al_destroy(ArrayList **list) {
    if(!list) return false;
    if(!*list) return false;
	if((*list)->destroy_function) al_iterate(*list, &_destroy_iter, *list);
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

LinkedList *ll_create(size_t size_elements) {
	return ll_create_full(size_elements, NULL, NULL);
}

LinkedList *ll_create_comparator(size_t size_elements, compare_fn compare_function) {
	return ll_create_full(size_elements, compare_function, NULL);
}

LinkedList *ll_create_destroyer(size_t size_elements, destroy_fn destroy_function) {
	return ll_create_full(size_elements, NULL, destroy_function);
}

LinkedList *ll_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
    LinkedList *list = ll_alloc();
    if(!list) return NULL;
    list->size_elements = size_elements;
	if(compare_function) list->compare_function = compare_function;
	else list->compare_function = &memcmp;
	list->destroy_function = destroy_function;
    return list;
}

void ll_change_comparator(LinkedList *list, compare_fn compare_function) {
	if(!list || !compare_function) return;
	list->compare_function = compare_function;
}

void ll_change_destroyer(LinkedList *list, destroy_fn destroy_function) {
	if(!list || !destroy_function) return;
	list->destroy_function = destroy_function;
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
        if(!list->head) return false;
        list->head->before = list->head;
        list->head->next = list->head;
        list->tail = list->head;
        list->count += 1;
        return true;
    }
    list->tail->next = ll_create_node(val, list->size_elements);
    if(!list->tail->next) return false;
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
        if(!list->head) return false;
		list->head->next = list->head;
		list->head->before = list->head;
        list->tail = list->head;
        list->count += 1;
        return true;
    }
    LLNode *p = ll_create_node(val, list->size_elements);
    if(!p) return false;
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
	LinkedList *new_l = ll_create_full(list->size_elements, list->compare_function, list->destroy_function);
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
	LinkedList *new_l = ll_create_full(list1->size_elements, list1->compare_function, list1->destroy_function);
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
		if(list->destroy_function) list->destroy_function(head->element);
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
	if(list->destroy_function) list->destroy_function(tail->element);
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
		if(list->destroy_function) list->destroy_function(head->element);
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
	if(list->destroy_function) list->destroy_function(head->element);
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
        list->head = NULL;
        list->tail = NULL;
		if(list->destroy_function) list->destroy_function(p->element);
		free(p->element);
        free(p);
		list->count--;
        return true;
    }
    LLNode *before = p->before;
    LLNode *next = p->next;
    before->next = next;
    next->before = before;
    if(p == list->head) list->head = next;
    if(p == list->tail) list->tail = before;
	if(list->destroy_function) list->destroy_function(p->element);
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
		if(list->destroy_function) list->destroy_function(p->element);
		free(val);
        free(p);
        return true;
    }
    LLNode *before = p->before;
    LLNode *next = p->next;
    before->next = next;
    next->before = before;
    if(p == list->head) list->head = next;
    if(p == list->tail) list->tail = before;
	if(out_ptr) memmove(out_ptr, p->element, list->size_elements);
	if(list->destroy_function) list->destroy_function(p->element);
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
	if(!list) return NULL;
    if(pos == 0) return list->head;
    if(pos == list->count - 1) return list->tail;
    LLNode *p = list->head;
    for(size_t i = 0; i < pos; i++)
        p = p->next;
    return p;
}

bool ll_destroy(LinkedList **list) {
    if(!list) return false;
    if(!*list) return false;
    if(!(*list)->head) {
        free(*list);
        *list = NULL;
        return true;
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
	return true;
}

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
    hs->list = al_create(sizeof(LinkedList*));
    if(!hs->list) {
        free(hs);
        return NULL;
    }
	LinkedList **elements = hs->list->elements;
    for(size_t i = 0; i < hs->list->len; i++) elements[i] = NULL;
	hs->list->count = hs->list->len;
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
    return (float)hs->count/hs->list->len;
}

bool hs_has_pos(HashSet *hs, void *val, size_t position) {
    if(!hs || !val) return false;
	if(!hs->list) return false;
	LinkedList *entry = *(LinkedList**)al_get_ith(hs->list, position);
	if(!entry) return false;
    return ll_get_node(entry, val) != NULL;
}

bool hs_has(HashSet *hs, void *val) {
	if(!hs || !val) return false;
	size_t pos = hs_hash_val(hs, val, hs->size_elements);
	return hs_has_pos(hs, val, pos);
}

bool hs_add_val(HashSet *hs, void *val, size_t position) {
    if(!hs || !val) return false;
    LinkedList *ith = *(LinkedList**)al_get_ith(hs->list, position);
    if(!ith) {
        ith = ll_create_full(hs->size_elements, hs->compare_function, hs->destroy_function);
		*(LinkedList**)al_get_ith(hs->list, position) = ith;
	}
	return ll_add_tail(ith, val);
}

bool hs_rehash(HashSet *hs) {
    if(!hs) return false;
    ArrayList *new = al_create_sized(sizeof(LinkedList*), hs->list->len * 2);
    new->count = new->len;
	memset(new->elements, 0, sizeof(LinkedList*) * new->len);
    for(size_t i = 0; i < hs->list->len; i++) {
        LinkedList *elements = *(LinkedList**)al_get_ith(hs->list, i);
        if(!elements) continue;
		if(!elements->head) {
			ll_destroy(&elements);
			continue;
		}
        LLNode *p = elements->head;
        for(size_t j = 0; j < elements->count; j++) {
            size_t ith = hs_hash_function(p->element, hs->size_elements) % new->len;
            LinkedList *new_entry = *(LinkedList**)al_get_ith(new, ith);
            if(!new_entry) {
                new_entry = ll_create_full(hs->size_elements, hs->compare_function, hs->destroy_function);
				*(LinkedList**)al_get_ith(new, ith) = new_entry;
			}
			ll_add_tail(new_entry, p->element);
			p = p->next;
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
    if(hs_has_pos(hs, val, pos)) return false;
    if(hs_add_val(hs, val, pos)) hs->count++;
    if(hs_load_factor(hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hs);
    return true;
}

bool hs_remove(HashSet *hs, void *val) {
    if(!hs || !val) return NULL;
    LinkedList *ith = *(LinkedList**)al_get_ith(hs->list, hs_hash_val(hs, val, hs->size_elements));
	bool r = ll_remove_val(ith, val);
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
		LinkedList *list = *(LinkedList**)al_get_ith((*hs)->list, i);
        ll_destroy(&list);
	}
	al_destroy(&((*hs)->list));
    free(*hs);
    *hs = NULL;
    return true;
}

HashMap *hm_create(size_t size_key, size_t size_value) {
	return hm_create_full(size_key, size_value, NULL, NULL, NULL, NULL);
}

void _hmp_destroy(void *element) {
	HashMapPair *hmp = element;
	free(hmp->key);
	free(hmp->value);
}

HashMap *hm_create_full(size_t size_key, size_t size_value, compare_fn compare_key, compare_fn compare_value, destroy_fn destroy_key, destroy_fn destroy_value) {
	HashMap *hm = malloc(sizeof(*hm));
	if(!hm) return NULL;
	hm->hs = hs_create(sizeof(HashMapPair));
	if(!(hm->hs)) {
		free(hm);
		return NULL;
	}
	hs_change_destroyer(hm->hs, _hmp_destroy);
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
	HashMapPair new_entry = {0};
	new_entry.key = malloc(hm->size_key);
	new_entry.value = malloc(hm->size_value);
	if(!new_entry.key || !new_entry.value) {
		if(new_entry.key) free(new_entry.key);
		if(new_entry.value) free(new_entry.value);
		return false;
	}
	memcpy(new_entry.key, key, hm->size_key);
	memcpy(new_entry.value, value, hm->size_value);
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
	if(hs_add_val(hm->hs, &new_entry, pos)) hm->hs->count++;
	if(hs_load_factor(hm->hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hm->hs);
	return true;
}

bool hm_has_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
    LinkedList *ll = *(LinkedList**)al_get_ith(hm->hs->list, pos);
	if(!ll) return false;
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
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
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
    LinkedList *ll = *(LinkedList**)al_get_ith(hm->hs->list, pos);
	if(!ll) return NULL;
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
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
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
    LinkedList *ll = *(LinkedList**)al_get_ith(hm->hs->list, pos);
	if(!ll) return false;
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
	    if(hm->destroy_key) hm->destroy_key(hmp->key);
	    if(hm->destroy_value) hm->destroy_value(hmp->value);
	
	    free(hmp->key);
	    free(hmp->value);
	
	    return ll_remove_val(ll, hmp);
	}
	return false;
}

bool hm_remove_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->count; i++) {
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
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
   			if(hm->destroy_key) hm->destroy_key(hmp->key);
		    if(hm->destroy_value) hm->destroy_value(hmp->value);
		
		    free(hmp->key);
		    free(hmp->value);
		
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
	size_t counting = (list->count * sizeof(LinkedList*)) + (hm->hs->count * (sizeof(HashMapPair) + hm->size_key + hm->size_value));
	for(size_t i = 0; i < list->count; i++) {
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
		structs += sizeof(LinkedList);
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
	for(size_t i = 0; i < (*hm)->hs->list->len; i++) {
		LinkedList *ll = ((LinkedList**)((*hm)->hs->list->elements))[i];
		if(!ll) continue;
		LLNode *p = ll->head;
		do {
			HashMapPair* element = p->element;
			if((*hm)->destroy_key) (*hm)->destroy_key(element->key);
			if((*hm)->destroy_value) (*hm)->destroy_value(element->value);
			p = p->next;
		} while(p != ll->head);
	}
	if(!hs_destroy(&((*hm)->hs))) return false;
	free(*hm);
	*hm = NULL;
	return true;
}

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

BinaryTree *bt_create(size_t size_elements) {
	return bt_create_full(size_elements, NULL, NULL);
}

BinaryTree *bt_create_comparator(size_t size_elements, compare_fn compare_function) {
	return bt_create_full(size_elements, compare_function, NULL);
}

BinaryTree *bt_create_destroyer(size_t size_elements, destroy_fn destroy_function) {
	return bt_create_full(size_elements, NULL, destroy_function);
}

BinaryTree *bt_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
	BinaryTree *bst = malloc(sizeof(*bst));
	if(!bst) return NULL;
	bst->root = NULL;
	bst->size_elements = size_elements;
	if(compare_function) bst->compare_function = compare_function;
	else bst->compare_function = &memcmp;
	bst->destroy_function = destroy_function;
	return bst;
}

void bt_change_comparator(BinaryTree *tree, compare_fn compare_function) {
	if(!tree || !compare_function) return;
	tree->compare_function = compare_function;
}

void bt_change_destroyer(BinaryTree *tree, destroy_fn destroy_function) {
	if(!tree || !destroy_function) return;
	tree->destroy_function = destroy_function;
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
				bt_destroy_node(to_free, root->destroy_function);
				return node;
			}
			aux = node;
			node = NULL;
			bt_destroy_node(aux, root->destroy_function);
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

bool bt_destroy_node(BinaryTreeNode *node, destroy_fn destroy_function) {
	if(!node) return false;
	bt_destroy_node(node->left, destroy_function);
	bt_destroy_node(node->right, destroy_function);
	if(destroy_function) destroy_function(node->element);
	free(node->element);
	free(node);
	return true;
}

bool bt_destroy(BinaryTree **root) {
	if(!root || !(*root)) return false;
	bt_destroy_node((*root)->root, (*root)->destroy_function);
	free(*root);
	*root = NULL;
	return true;
}

AbstractTree *at_create(void *val, size_t size_elements) {
	return at_create_full(val, size_elements, NULL, NULL);
}

AbstractTree *at_create_full(void *val, size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
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

void at_change_comparator(AbstractTree *tree, compare_fn compare_function) {
	if(!tree || !compare_function) return;
	tree->compare_function = compare_function;
}

void at_change_destroyer(AbstractTree *tree, destroy_fn destroy_function) {
	if(!tree || !destroy_function) return;
	tree->destroy_function = destroy_function;
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

#ifdef STRCTS_TEST

#define TEST(cond, msg) \
    do { \
        if (!(cond)) { \
            printf("FAIL: %s\n", msg); \
            exit(1); \
        } else { \
            printf("PASS: %s\n", msg); \
        } \
    } while(0)

void test_array() {
    int *arr = NULL;

    // ---- create + add ----
    array_add(arr, 10);
    array_add(arr, 20);
    array_add(arr, 30);

    TEST(array_size(arr) == 3, "array_add increases size");
    TEST(arr[0] == 10 && arr[1] == 20 && arr[2] == 30, "array_add stores values");

    // ---- add at position ----
    array_add_at(arr, 15, 1);
    TEST(array_size(arr) == 4, "array_add_at increases size");
    TEST(arr[1] == 15, "array_add_at inserts correctly");

    // ---- add many ----
    int more[] = {40, 50, 60};
    array_add_many(arr, more, 3);

    TEST(array_size(arr) == 7, "array_add_many works");
    TEST(arr[4] == 40 && arr[6] == 60, "array_add_many values correct");

    // ---- add many at position ----
    int more2[] = {100, 200};
    array_add_many_at(arr, more2, 2, 2);

    TEST(array_size(arr) == 9, "array_add_many_at size");
    TEST(arr[2] == 100 && arr[3] == 200, "array_add_many_at values");

    // ---- has ----
    size_t pos = 0;
    TEST(array_has(arr, 200, &pos), "array_has finds element");
    TEST(arr[pos] == 200, "array_has correct position");

    // ---- remove at ----
	int out;
    array_remove_at(arr, 2, &out);
    TEST(out == 100, "array_remove_at returns correct value");
    TEST(array_size(arr) == 8, "array_remove_at reduces size");

    // ---- remove fast ----
    int last_before = arr[array_size(arr) - 1];
    array_remove_at_fast(arr, 1, &out);
    TEST(array_size(arr) == 7, "array_remove_at_fast reduces size");
    TEST(arr[1] == last_before, "array_remove_at_fast swaps with last");

    // ---- pop ----
    array_pop(arr, &out);
    TEST(array_size(arr) == 6, "array_pop reduces size");

    // ---- remove value ----
    array_remove_val(arr, 50);
    TEST(!array_has(arr, 50, &pos), "array_remove_val removes value");

    // ---- clear ----
    array_clear(arr);
    TEST(array_size(arr) == 0, "array_clear resets size");
    TEST(array_is_empty(arr), "array_is_empty works");

    // ---- reuse after clear ----
    array_add(arr, 999);
    TEST(array_size(arr) == 1 && arr[0] == 999, "array works after clear");

    // ---- destroy ----
    array_destroy(arr);
    TEST(arr == NULL, "array_destroy sets NULL");
}

void _sum_iter(void *e, void *arg) {
    *(int*)arg += *(int*)e;
}

void test_al() {
    ArrayList *list = al_create(sizeof(int));

    TEST(al_is_empty(list), "ArrayList starts empty");

    int vals[] = {10, 20, 30, 40, 50};

    // add many
    for (int i = 0; i < 5; i++)
        al_add(list, &vals[i]);

    TEST(al_size(list) == 5, "ArrayList add multiple");

    // access
    for (int i = 0; i < 5; i++) {
        int *v = al_get_ith(list, i);
        TEST(*v == vals[i], "ArrayList values correct");
    }

    // insert in middle
    int x = 25;
    al_add_at(list, &x, 2);
    TEST(*(int*)al_get_ith(list, 2) == 25, "ArrayList insert at");

    // iterate
    int sum = 0;
    al_iterate(list, _sum_iter, &sum);
    TEST(sum == 175, "ArrayList iterate");

    // has
    size_t pos;
    TEST(al_has(list, &x, &pos), "ArrayList has");
    TEST(pos == 2, "ArrayList has correct position");

    // remove
    int out;
    al_remove_at(list, 2, &out);
    TEST(out == 25, "ArrayList remove_at value");

    // fast remove
    int last = *(int*)al_get_ith(list, al_size(list) - 1);
    al_remove_at_fast(list, 1, &out);
    TEST(*(int*)al_get_ith(list, 1) == last, "ArrayList fast remove swap");

    // pop
    al_pop(list, &out);
    TEST(al_size(list) == 3, "ArrayList pop");

    // clear
    al_clear(list);
    TEST(al_is_empty(list), "ArrayList clear");

    al_destroy(&list);
    TEST(list == NULL, "ArrayList destroy");
}

void test_ll() {
    LinkedList *list = ll_create(sizeof(int));

    int vals[] = {1, 2, 3, 4, 5};

    // add head & tail
    ll_add_head(list, &vals[0]);
    ll_add_tail(list, &vals[1]);
    ll_add_tail(list, &vals[2]);

    TEST(list->count == 3, "LinkedList add head/tail");

    // add at
    ll_add_at(list, &vals[3], 1);
    TEST(list->count == 4, "LinkedList add_at");

    // find
    LLNode *n = ll_get_node(list, &vals[3]);
    TEST(n != NULL, "LinkedList find");

    // remove head
    int out;
    ll_remove_head(list, &out);
    TEST(out == 1, "LinkedList remove head");

    // remove tail
    ll_remove_tail(list, &out);
    TEST(out == 3, "LinkedList remove tail");

    // remove middle
    ll_remove_val(list, &vals[3]);
    TEST(list->count == 1, "LinkedList remove middle");

    // iterate
    int sum = 0;
    ll_iterate(list, _sum_iter, &sum);
    TEST(sum == 2, "LinkedList iterate");

    ll_destroy(&list);
    TEST(list == NULL, "LinkedList destroyed");
}

void test_set() {
    HashSet *hs = hs_create(sizeof(int));

    int vals[] = {10, 20, 30, 40};

    // insert
    for (int i = 0; i < 4; i++)
        hs_add(hs, &vals[i]);

    TEST(hs_size(hs) == 4, "HashSet insert");

    // duplicate
    TEST(!hs_add(hs, &vals[0]), "HashSet reject duplicate");

    // has
    TEST(hs_has(hs, &vals[2]), "HashSet has");

    // remove
    hs_remove(hs, &vals[2]);
    TEST(hs_size(hs) == 3, "HashSet remove");

    // stress insert
    for (int i = 0; i < 1000; i++) {
        int v = i + 100;
        hs_add(hs, &v);
    }

    TEST(hs_size(hs) >= 1000, "HashSet stress insert");

    hs_destroy(&hs);
    TEST(hs == NULL, "HashSet destroy");
}

void test_map() {
    HashMap *hm = hm_create(sizeof(int), sizeof(int));

    int keys[] = {1, 2, 3};
    int vals[] = {100, 200, 300};

    // insert
    for (int i = 0; i < 3; i++)
        hm_add(hm, &keys[i], &vals[i]);

    TEST(hm_size(hm) == 3, "HashMap insert");

    // get
    for (int i = 0; i < 3; i++) {
        int *v = hm_get_value(hm, &keys[i]);
        TEST(*v == vals[i], "HashMap get");
    }

    // has key/value
    TEST(hm_has_key(hm, &keys[1]), "HashMap has key");
    TEST(hm_has_value(hm, &vals[2]), "HashMap has value");

    // remove key
    hm_remove_key(hm, &keys[1]);
    TEST(!hm_has_key(hm, &keys[1]), "HashMap remove key");

    // remove value
    hm_remove_value(hm, &vals[2]);
    TEST(!hm_has_value(hm, &vals[2]), "HashMap remove value");

    // stress
    for (int i = 0; i < 1000; i++) {
        int k = i + 10;
        int v = i * 2;
        hm_add(hm, &k, &v);
    }

    TEST(hm_size(hm) >= 1000, "HashMap stress");

    hm_destroy(&hm);
    TEST(hm == NULL, "HashMap destroy");
}

void test_bst() {
    BinaryTree *bt = bt_create(sizeof(int));

    int vals[] = {50, 30, 70, 20, 40, 60, 80};

    // insert
    for (int i = 0; i < 7; i++)
        bt_insert(bt, &vals[i]);

    // search
    for (int i = 0; i < 7; i++) {
        TEST(bt_search(bt, &vals[i]) != NULL, "BinaryTree search");
    }

    // remove leaf
    bt_remove(bt, &vals[3]);
    TEST(bt_search(bt, &vals[3]) == NULL, "BinaryTree remove leaf");

    // remove root
    bt_remove(bt, &vals[0]);
    TEST(bt_search(bt, &vals[0]) == NULL, "BinaryTree remove root");

    // balance check
    TEST(bt_is_balanced(bt->root), "BinaryTree remains balanced");

    bt_destroy(&bt);
    TEST(bt == NULL, "BinaryTree destroy");
}

void test_absttree() {
    int a = 1, b = 2, c = 3, d = 4;

    AbstractTree *root = at_create(&a, sizeof(int));
    AbstractTree *c1 = at_create(&b, sizeof(int));
    AbstractTree *c2 = at_create(&c, sizeof(int));
    AbstractTree *c3 = at_create(&d, sizeof(int));

    // build structure
    at_add_child(root, c1);
    at_add_child(root, c2);
    at_add_child(c1, c3);

    TEST(root->child == c1, "AbstractTree first child");
    TEST(c1->sibling == c2, "AbstractTree sibling");
    TEST(c1->child == c3, "AbstractTree nested child");

    at_destroy(&root);
    TEST(root == NULL, "AbstractTree destroy");
}

void main_tests() {
	test_array();
    test_al();
    test_ll();
    test_set();
    test_map();
    test_bst();
    test_absttree();
}

#endif //STRCTS_TEST

