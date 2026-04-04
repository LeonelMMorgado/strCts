#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "memclass.h"
#include "iter.h"

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
void        ll_concat_list(LinkedList *list1, LinkedList *list2);
LinkedList *ll_concat_list_new(LinkedList *list1, LinkedList *list2);

LLNode *ll_get_node(LinkedList *list, void *val);
LLNode *ll_get_node_at(LinkedList *list, size_t pos);

void ll_iterate(LinkedList *list, iter_fn func, void *arg);

bool ll_remove_tail(LinkedList *list, void *out_ptr);
bool ll_remove_head(LinkedList *list, void *out_ptr);
bool ll_remove_val(LinkedList *list, void *val);
bool ll_remove_at(LinkedList *list, size_t pos, void *out_ptr);

void ll_destroy(LinkedList **list);

#endif
