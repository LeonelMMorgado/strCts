#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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

LinkedList *ll_create(size_t size_element);

bool ll_add_tail(LinkedList *list, void *val, size_t size_element);
bool ll_add_head(LinkedList *list, void *val, size_t size_element);
bool ll_add_at(LinkedList *list, void *val, size_t size_element, size_t pos);
bool ll_add_many(LinkedList *list, void *elements, size_t elements_count, size_t elements_size);
bool ll_add_many_at(LinkedList *list, void *elements, size_t elements_count, size_t elements_size, size_t pos);

LinkedList *ll_copy_list(LinkedList *list);
LinkedList *ll_concat_list(LinkedList *list1, LinkedList *list2);

LLNode *ll_get_node(LinkedList *list, void *val);
LLNode *ll_get_node_at(LinkedList *list, size_t pos);

bool ll_remove_tail(LinkedList *list);
bool ll_remove_head(LinkedList *list);
bool ll_remove_val(LinkedList *list, void *val);
bool ll_remove_at(LinkedList *list, size_t pos);

void ll_destroy(LinkedList **list);

#endif
