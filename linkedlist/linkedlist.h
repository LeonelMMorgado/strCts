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

LinkedList *ll_create_linkedlist();
LinkedList *ll_alloc_linked_list(size_t size_element);
LLNode *ll_create_node(void *val, size_t element_size);

bool ll_append_tail(LinkedList *list, void *val, size_t size_element);
bool ll_append_head(LinkedList *list, void *val, size_t size_element);
//bool ll_append_at()

void *ll_remove_tail(LinkedList *list);
void *ll_remove_head(LinkedList *list);
void *ll_remove_val(LinkedList *list, void *val);
void *ll_remove_at(LinkedList *list, size_t pos);

LLNode *ll_get_node(LinkedList *list, void *val);
LLNode *ll_get_node_at(LinkedList *list, size_t pos);

void ll_free(LinkedList *list);

#endif