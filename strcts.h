#ifndef _STRCTS_H
#define _STRCTS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

//ArrayList definitions
typedef struct _arrlist {
    void *elements;
    size_t count;
    size_t len;
    size_t size_elements;
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
    size_t element_size;
    size_t len;
} LinkedList;

//HashSet definitions
#define HS_MAX_LOAD_FACTOR 0.8
typedef struct _hs_entry {
    void *element;
    bool valid_entry;
} HashEntry;
typedef struct _hash_table {
    ArrayList *list;
    uint16_t size_element;
    size_t count;
} HashSet;

//HashMap definitions
typedef struct _hash_map_pair {
	void *key;
	void *value;
} HashMapPair;
typedef struct _hash_map {
	HashSet *hs;
	size_t key_size;
	size_t value_size;
} HashMap;

//BinaryTree definitions
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
typedef struct _bstree_node {
	void *val;
	struct _bstree_node *left;
	struct _bstree_node *right;
	int64_t height;
} BinaryTreeNode;
typedef int (*cmp_function)(const void *val1, const void *val2, size_t element_size);
typedef struct _binary_search_tree {
    size_t size_element;
    BinaryTreeNode *root;
	cmp_function compare_function;
} BinaryTree;

//AbstractTree definitions
typedef struct _abstract_tree {
	void *val;
	size_t size;
	struct _abstract_tree *child;
	struct _abstract_tree *sibling;
} AbstractTree;

#ifdef __cplusplus
extern "C" {
#endif

//ArrayList functions
ArrayList *al_create(size_t element_size);
ArrayList *al_create_sized(size_t element_size, size_t len);
bool       al_realloc(ArrayList *list);
bool al_input_unsafe(ArrayList *list, void *new_element, size_t position);
bool al_add(ArrayList *list, void *new_element);
bool al_push(ArrayList *list, void *new_element);
bool al_add_at(ArrayList *list, void *new_element, size_t pos);
bool al_add_many(ArrayList *list, void *elements, size_t elements_count);
bool al_add_many_at(ArrayList *list, void *elements, size_t elements_count, size_t pos);
bool al_update(ArrayList *list, void *update, size_t pos);
ArrayList *al_copy_list(ArrayList *list);
ArrayList *al_concat_list(ArrayList *l1, ArrayList *l2);
bool al_is_empty(ArrayList *list);
bool al_has(ArrayList *list, void *val, size_t *pos);
bool al_has_at(ArrayList *list, void *val, size_t pos);
void *al_get_ith(ArrayList *list, size_t i);
bool al_remove_at(ArrayList *list, size_t pos, void *out_ptr);
bool al_remove_at_fast(ArrayList *list, size_t pos, void *out_ptr); /*changes array order*/
bool al_pop(ArrayList *list, void *out_ptr);
bool al_remove_first(ArrayList *list, void *out_ptr);
bool al_remove_val(ArrayList *list, void *val);
bool al_clear(ArrayList *list);
bool al_destroy(ArrayList **list);

//LinkedList functions
LinkedList *ll_create(size_t size_element);
bool ll_add_tail(LinkedList *list, void *val);
bool ll_add_head(LinkedList *list, void *val);
bool ll_add_at(LinkedList *list, void *val, size_t pos);
bool ll_add_many(LinkedList *list, void *elements, size_t elements_count);
bool ll_add_many_at(LinkedList *list, void *elements, size_t elements_count, size_t pos);
LinkedList *ll_copy_list(LinkedList *list);
LinkedList *ll_concat_list(LinkedList *list1, LinkedList *list2);
LLNode *ll_get_node(LinkedList *list, void *val);
LLNode *ll_get_node_at(LinkedList *list, size_t pos);
bool ll_remove_tail(LinkedList *list, void *out_ptr);
bool ll_remove_head(LinkedList *list, void *out_ptr);
bool ll_remove_val(LinkedList *list, void *val);
bool ll_remove_at(LinkedList *list, size_t pos, void *out_ptr);
void ll_destroy(LinkedList **list);

//HashSet functions
HashSet *hs_create(size_t element_size);
uint64_t hs_hash_function(void *val, size_t element_size);
size_t hs_hash_val(HashSet *hs, void *val, size_t element_size);
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
HashMap *hm_create(size_t size_key, size_t size_value);
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
//basic compare functions for inclusion search and removal in binary tree
int bt_common_int_compare(const void *val1, const void *val2, size_t element_size);
int bt_common_uint_compare(const void *val1, const void *val2, size_t element_size);
int bt_common_i64_compare(const void *val1, const void *val2, size_t element_size);
int bt_common_u64_compare(const void *val1, const void *val2, size_t element_size);
int bt_common_float_compare(const void *val1, const void *val2, size_t element_size);
int bt_common_double_compare(const void *val1, const void *val2, size_t element_size);
int bt_common_string_compare(const void *val1, const void *val2, size_t element_size);
BinaryTreeNode *bt_create_node(void *val, size_t element_size);
BinaryTree *bt_create(size_t element_size, cmp_function compare_function);
int64_t bt_height(BinaryTreeNode *root);
void bt_update_height(BinaryTreeNode *root);
int64_t bt_balance(BinaryTreeNode *root);
bool bt_is_balanced(BinaryTreeNode *root);
bool bt_insert(BinaryTree *root, void *val);
bool bt_remove(BinaryTree *root, void *val);
BinaryTreeNode *bt_search(BinaryTree *root, void *val);
// BinaryTreeNode *bt_invert_tree(BinaryTreeNode *root);
void bt_print(BinaryTree *root, int rows, int cols);
void bt_delete_node(BinaryTreeNode *node);
void bt_delete(BinaryTree **root);

//AbstractTree functions
AbstractTree *at_create(void *val, size_t size);
void at_add_child(AbstractTree* parent, AbstractTree* child);
void at_print_tree(AbstractTree *root);

#ifdef __cplusplus
}
#endif

#endif //_STRCTS_H

#ifdef STRCTS_IMPLEMENTATION

ArrayList *al_alloc() {
    ArrayList *list = calloc(1, sizeof(*list));
    return list;
}

ArrayList *al_create(size_t element_size) {
    ArrayList *list = al_alloc();
    if(!list) return NULL;
    list->elements = calloc(256, element_size);
    if(!(list->elements)) {
        free(list);
        return NULL;
    }
    list->len = 256;
    list->size_elements = element_size;
    return list;
}

ArrayList *al_create_sized(size_t element_size, size_t len) {
    ArrayList *list = al_alloc();
    if(!list) return NULL;
    list->elements = calloc(len, element_size);
    if(!(list->elements)) {
        free(list);
        return NULL;
    }
    list->len = len;
    list->size_elements = element_size;
    return list;
}

bool al_realloc(ArrayList *list) {
    if(!list) return false;
	if(list->size_elements * list->len * 2 < list->size_elements * list->len) return false;
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
            void *check = realloc(list->elements, list->size_elements * list->len * 2);
            if(!check) return false;
            list->elements = check;
            list->len *= 2;
        }
    }
	memmove((uint8_t*)list->elements + (list->count * list->size_elements), elements, list->size_elements);
	list->count += elements_count;
    return true;
}

bool al_add_many_at(ArrayList *list, void *elements, size_t elements_count, size_t pos) {
	if(!list || !elements) return false;
	if(list->count <= pos) return al_add_many(list, elements, elements_count);
	if(!list->count + elements_count >= list->len) {
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
    ArrayList *cpy = al_create(list->size_elements);
	memmove(cpy, list->elements, list->count);
    return cpy;
}

ArrayList *al_concat_list(ArrayList *l1, ArrayList *l2) {
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

bool al_is_empty(ArrayList *list) {
    return !list || list->count == 0;
}

bool al_has(ArrayList *list, void *val, size_t *pos) {
    if(!list || !val) return false;
    for(size_t i = 0; i < list->count; i++) {
        bool found = true;
        uint8_t *s1 = (uint8_t *)list->elements + (i * list->size_elements);
        if(memcmp(s1, val, list->size_elements) != 0) 
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
    if(memcmp(s1, val, list->size_elements) != 0) found = false;
    return found;
}

void *al_get_ith(ArrayList *list, size_t i) {
    if(!list || i > list->count) return NULL;
    if(list->count < i) return NULL;
    return (uint8_t *)list->elements + (list->size_elements * i);
}

bool al_remove_at(ArrayList *list, size_t pos, void *out_ptr) {
    if(!list) return false;
    if(list->count == 0 || list->count <= pos) return false;
    void *src = (uint8_t*)list->elements + (list->size_elements * pos);
    if(out_ptr) memmove(out_ptr, src, list->size_elements);
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

bool al_destroy(ArrayList **list) {
    if(!list) return false;
    if(!*list) return false;
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

LinkedList *ll_create(size_t size_element) {
    LinkedList *list = ll_alloc();
    if(!list) return NULL;
    list->element_size = size_element;
    return list;
}

LLNode *ll_create_node(void *val, size_t element_size) {
    if(!val) return NULL;
    LLNode *node = calloc(1, sizeof(*node));
    if(!node) return NULL;
    node->before = NULL;
    node->next = NULL;
    node->element = malloc(element_size);
    if(!node->element) {
        free(node);
        return NULL;
    }
    memmove((uint8_t *)node->element, (uint8_t *)val, element_size);
    return node;
}

bool ll_add_tail(LinkedList *list, void *val) {
    if(!list || !val) return false;
    if(!list->head) {
        list->head = ll_create_node(val, list->element_size);
        if(!list->head) return NULL;
        list->head->before = list->head;
        list->head->next = list->head;
        list->tail = list->head;
        list->len += 1;
        return true;
    }
    list->tail->next = ll_create_node(val, list->element_size);
    if(!list->tail->next) return NULL;
    LLNode *p = list->tail->next;
    p->before = list->tail;
    list->tail = p;
    list->tail->next = list->head;
    list->head->before = list->tail;
    list->len += 1;
    return true;
}

bool ll_add_head(LinkedList *list, void *val) {
    if(!list || !val) return false;
    if(!list->head) {
        list->head = ll_create_node(val, list->element_size);
        if(!list->head) return NULL;
        list->tail = list->head;
        list->len += 1;
        return true;
    }
    LLNode *p = ll_create_node(val, list->element_size);
    if(!p) return NULL;
    p->next = list->head;
    list->head->before = p;
    list->head = p;
    list->head->before = list->tail;
    list->tail->next = list->head;
    list->len += 1;
    return true;
}

bool ll_add_at(LinkedList *list, void *val, size_t pos) {
	if(!list || !val) return false;
	if(pos == 0) return ll_add_head(list, val);
	if(pos == list->len - 1) return ll_add_tail(list, val);
	size_t i = 0;
	LLNode *p = list->head;
	while(p) {
		if(i == pos) break;
		p = p->next;
		i++;
	}
	p->before->next = ll_create_node(val, list->element_size);
	if(!(p->before->next)) return false;
	p->before = p->before->next;
	list->len += 1;
	return true;
}

bool ll_add_many_at(LinkedList *list, void *elements, size_t elements_count, size_t pos) {
	if(!list || !elements) return false;
	LLNode *first = ll_create_node(elements, list->element_size);
	LLNode *last = first;
	for(size_t i = 1; i < elements_count; i++) {
		last->next = ll_create_node((uint8_t*)elements + (i * list->element_size), list->element_size);
		last->next->before = last;
		last = last->next;
	}
	LLNode *node_at_pos = ll_get_node_at(list, pos);
	node_at_pos->before->next = first;
	first->before = node_at_pos->before;
	node_at_pos->before = last;
	last->next = node_at_pos;

	if(pos == 0) list->head = first;
	if(pos >= list->len) list->tail = last;
	list->len += elements_count;
	return true;
}

bool ll_add_many(LinkedList *list, void *elements, size_t elements_count) {
	if(!list || !elements) return false;
	return ll_add_many_at(list, elements, elements_count, list->len);
}

LinkedList *ll_copy_list(LinkedList *list) {
	if(!list) return NULL;
	LinkedList *new_l = ll_create(list->element_size);
	if(!new_l) return NULL;
	LLNode *p = list->head;
	for(size_t i = 0; i < list->len; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_add_tail(new_l, p->element);
		p = p->next;
	}
	return new_l;
}

LinkedList *ll_concat_list(LinkedList *list1, LinkedList *list2) {
	if(!list1 || !list2) return NULL;
	LinkedList *new_l = ll_create(list1->element_size);
	if(!new_l) return NULL;
	LLNode *p = list1->head;
	for(size_t i = 0; i < list1->len; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_add_tail(new_l, p->element);
		p = p->next;
	}
	p = list2->head;
	for(size_t i = 0; i < list2->len; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_add_tail(new_l, p->element);
		p = p->next;
	}
	return new_l;
}

bool ll_remove_tail(LinkedList *list, void *out_ptr) {
    if(!list) return false;
    if(!list->head) return false;
    if(list->head == list->tail) {
        LLNode *head = list->head->element;
		if(out_ptr) memmove(out_ptr, head->element, list->element_size);
		free(head->element);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->len--;
        return true;
    }
    LLNode *tail = list->tail;
    tail->before->next = list->head;
    list->head->before = tail->before;
    list->tail = tail->before;
	if(out_ptr) memmove(out_ptr, tail->element, list->element_size);
	free(tail->element);
    free(tail);
    list->len--;
    return true;
}

bool ll_remove_head(LinkedList *list, void *out_ptr) {
    if(!list) return false;
    if(!list->head) return false;
    if(list->head == list->tail) {
        LLNode *head = list->head->element;
		if(out_ptr) memmove(out_ptr, head->element, list->element_size);
		free(head->element);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->len--;
        return true;
    }
    LLNode *head = list->head;
    head->next->before = list->tail;
    list->tail->next = head->next;
    list->head = head->next;
	if(out_ptr) memmove(out_ptr, head->element, list->element_size);
	free(head->element);
    free(head);
    list->len--;
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
    list->len--;
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
		if(out_ptr) memmove(out_ptr, val, list->element_size);
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
	if(out_ptr) memmove(out_ptr, p->element, list->element_size);
	free(p->element);
    free(p);
    list->len--;
    return true;
}

LLNode *ll_get_node(LinkedList *list, void *val) {
    if(!list || !val) return NULL;
    if(!list->head) return NULL;
    LLNode *p = list->head;
    do {
        if(memcmp((uint8_t *)p->element, (uint8_t *)val, list->element_size) == 0) return p;
        p = p->next;
    } while(p != list->head);
    return NULL;
}

LLNode *ll_get_node_at(LinkedList *list, size_t pos) {
    if(pos == 0) return list->head;
    if(pos == list->len - 1) return list->tail;
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
        free(p->element);
        LLNode *next = p->next;
        free(p);
        p = next;
    } while(p != head);
    free(*list);
    *list = NULL;
}

HashSet *hs_create(size_t element_size) {
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
    hs->list->count = hs->list->len;
    hs->size_element = element_size;
    hs->count = 0;
    return hs;
}

uint64_t hs_hash_function(void *val, size_t element_size) {
    if(!val) return 0;
    uint64_t hash = 0;
    uint8_t *c = val;
    for(size_t i = 0; i < element_size; i++)
        hash = (hash * 31) + c[i];
    return hash;
}

size_t hs_hash_val(HashSet *hs, void *val, size_t element_size) {
    if(!hs || !val) return 0;
    return hs_hash_function(val, element_size) % hs->list->len;
}

float hs_load_factor(HashSet *hs) {
    if(!hs) return -1;
    return (float)hs->count/hs->list->len;
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
        ith->element = ll_create(hs->size_element);
    return ll_add_tail(ith->element, val);
}

bool hs_rehash(HashSet *hs) {
    if(!hs) return false;
    ArrayList *new = al_create_sized(sizeof(HashEntry), hs->list->len * 2);
    new->count = new->len;
    for(size_t i = 0; i < new->len; i++) {
        HashEntry*ith = al_get_ith(new->elements, i);
        ith->valid_entry = false;
        ith->element = NULL;
    }
    for(size_t i = 0; i < hs->list->len; i++) {
        HashEntry *elements_at_i = al_get_ith(hs->list, i);
        if(!elements_at_i->valid_entry || !elements_at_i->element) continue;
		LinkedList *elements = elements_at_i->element;
        LLNode *p = elements->head;
        if(!p) continue;
        for(size_t j = 0; j < elements->len; j++) {
            size_t ith = hs_hash_function(p->element, hs->size_element) % new->len;
            HashEntry *new_entry = al_get_ith(new, ith);
            new_entry->valid_entry = true;
            if(!new_entry->element)
                new_entry->element = ll_create(hs->size_element);
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
    size_t pos = hs_hash_val(hs, val, hs->size_element);
    if(hs_has(hs, val, pos)) return false;
    if(hs_add_val(hs, val, pos)) hs->count++;
    if(hs_load_factor(hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hs);
    return true;
}

bool hs_remove(HashSet *hs, void *val) {
    if(!hs || !val) return NULL;
    HashEntry *ith = al_get_ith(hs->list, hs_hash_val(hs, val, hs->size_element));
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
    for(size_t i = 0; i < (*hs)->list->len; i++) {
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

HashMap *hm_create(size_t size_key, size_t size_value) {
	HashMap *hm = malloc(sizeof(*hm));
	if(!hm) return NULL;
	hm->hs = hs_create(sizeof(HashMapPair));
	if(!(hm->hs)) {
		free(hm);
		return NULL;
	}
	hm->key_size = size_key;
	hm->value_size = size_value;
	return hm;
}

bool hm_add(HashMap *hm, void *key, void *value) {
	if(!hm || !key || !value) return false;
	if(hm_has_key(hm, key)) //could return position?
		if(memcmp(hm_get_value(hm, key), value, hm->value_size) == 0) 
			return false;
	HashMapPair *new_entry = _hmp_create(key, value, hm->key_size, hm->value_size);
	if(!new_entry) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
	if(hs_add_val(hm->hs, new_entry, hs_hash_val(hm->hs, key, hm->key_size))) hm->hs->count++;
	if(hs_load_factor(hm->hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hm->hs);
	return true;
}

bool hm_has_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
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
		res = memcmp(hmp->key, key, hm->key_size);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return true;
	return false;
}

bool hm_has_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	bool found = false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->len; i++) {
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
			res = memcmp(hmp->value, value, hm->key_size);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) found = true;
		if(found) break;
	}
	return found;
}

void*hm_get_value(HashMap *hm, void *key) {
	if(!hm || !key) return NULL;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
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
		res = memcmp(hmp->key, key, hm->key_size);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return hmp->value;
	return NULL;
}

void*hm_get_key(HashMap *hm, void *value) {
	if(!hm || !value) return NULL;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->len; i++) {
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
			res = memcmp(hmp->value, value, hm->key_size);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) return hmp->key;
	}
	return NULL;
}

bool hm_remove_key(HashMap *hm, void *key) {
	if(!hm || !key) return NULL;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
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
		res = memcmp(hmp->key, key, hm->key_size);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) {
		ll_remove_val(ll, hmp);
	}
	return NULL;
}

bool hm_remove_value(HashMap *hm, void *value) {
	if(!hm || !value) return NULL;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->len; i++) {
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
			res = memcmp(hmp->value, value, hm->key_size);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) {
			ll_remove_val(ll, hmp);
		}
	}
	return NULL;
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
	size_t counting = (list->len * sizeof(HashEntry)) + (hm->hs->count * (sizeof(HashMapPair) + hm->key_size + hm->value_size));
	for(size_t i = 0; i < list->len; i++) {
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
	//FIXME: destroy all HashMapPairs;
	if(!hs_destroy(&((*hm)->hs))) return false;
	free(*hm);
	*hm = NULL;
	return true;
}

int64_t _bt_max_impl(int64_t a, int64_t b) {
	return a > b ? a : b;
}

int bt_common_int_compare(const void *val1, const void *val2, size_t element_size) {
	int v1 = *(int*)val1;
	int v2 = *(int*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_uint_compare(const void *val1, const void *val2, size_t element_size) {
	uint32_t v1 = *(uint32_t*)val1;
	uint32_t v2 = *(uint32_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_i64_compare(const void *val1, const void *val2, size_t element_size) {
	int64_t v1 = *(int64_t*)val1;
	int64_t v2 = *(int64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_u64_compare(const void *val1, const void *val2, size_t element_size) {
	uint64_t v1 = *(uint64_t*)val1;
	uint64_t v2 = *(uint64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_float_compare(const void *val1, const void *val2, size_t element_size) {
	float v1 = *(float*)val1;
	float v2 = *(float*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_double_compare(const void *val1, const void *val2, size_t element_size) {
	double v1 = *(double*)val1;
	double v2 = *(double*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_string_compare(const void *val1, const void *val2, size_t element_size) {
	char *s1 = *(char**)val1;
	char *s2 = *(char**)val2;
	return strcmp(s1, s2);
}

BinaryTreeNode *bt_create_node(void *val, size_t element_size) {
    BinaryTreeNode *n = malloc(sizeof(*n));
	if(!n)
		return NULL;
    n->val = malloc(element_size);
	if(!(n->val)) {
		free(n);
		return NULL;
	}
    memcpy(n->val, val, element_size);
	n->left = NULL;
	n->right = NULL;
	n->height = 0;
	return n;
}

BinaryTree *bt_create(size_t element_size, cmp_function compare_function) {
	BinaryTree *bst = malloc(sizeof(*bst));
	if(!bst) return NULL;
	bst->root = NULL;
	bst->size_element = element_size;
	if(compare_function)
		bst->compare_function = compare_function;
	else
		bst->compare_function = &memcmp;
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
	if(!node) return bt_create_node(val, root->size_element);
    int res = root->compare_function(node->val, val, root->size_element);
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
	int res = root->compare_function(node->val, val, root->size_element);
    if(res == 0) {
        if(!(node->left) || !(node->right)) {
			BinaryTreeNode *aux = node->left ? node->left : node->right;
			if(aux) {
				BinaryTreeNode *to_free = node;
				node = aux;
				to_free->left = NULL;
				to_free->right = NULL;
				bt_delete_node(to_free);
				return node;
			}
			aux = node;
			node = NULL;
			bt_delete_node(aux);
        }
		else {
			BinaryTreeNode *aux = node->left;
			while(aux->right)
				aux = aux->right;
			void *temp = node->val;
			node->val = aux->val;
			aux->val = temp;
			node->left = _bt_remove_internal(root, node->left, aux->val);
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
    int res = root->compare_function(node->val, val, root->size_element);
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
	sprintf(ptr, "%03d", *(int*)no->val);
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

void bt_delete_node(BinaryTreeNode *node) {
	if(!node) return;
	bt_delete_node(node->left);
	bt_delete_node(node->right);
	free(node);
}

void bt_delete(BinaryTree **root) {
	if(!root || !(*root)) return;
	bt_delete_node((*root)->root);
	free(*root);
	*root = NULL;
}

AbstractTree *at_create(void *val, size_t size) {
    AbstractTree* node = malloc(sizeof(*node));
    if(!node) return NULL;
    node->val = val;
    node->size = size;
    node->child = NULL;
    node->sibling = NULL;
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
    printf("%p\n", root->val); //add way to print accordingly
    AbstractTree* child = root->child;
    while(child != NULL) {
        _at_print_tree_rec(child, level + 1);
        child = child->sibling;
    }
}

void at_print_tree(AbstractTree *root) {
    _at_print_tree_rec(root, 0);
}
#endif //STRCTS_IMPLEMENTATION
