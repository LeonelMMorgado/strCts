#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "linkedlist.h"

#ifndef _STRING_H

static void *memmove(void *dest, const void *src, size_t n) {
    void *a = malloc(n);
    for(size_t i = 0; i < n; i++)
        *((uint8_t*)a + i) = *((uint8_t*)src + i);
    for(size_t i = 0; i < n; i++)
        *((uint8_t*)dest + i) = *((uint8_t*)a + i);
    free(a);
    return dest;
}

static uint32_t memcmp(const void *s1, const void *s2, size_t n) {
    uint32_t diff = 0;
    for(size_t i = 0; i < n; i++)
        diff += *((uint8_t*)s2 + i) - *((uint8_t*)s1 + i);
    return diff;
}

#endif

LinkedList *ll_create_linkedlist() {
    LinkedList *list = calloc(1, sizeof(*list));
    return list;
}

LinkedList *ll_alloc_linked_list(size_t size_element) {
    LinkedList *list = ll_create_linkedlist();
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
    memmove(node->element, val, element_size);
    // for(size_t i = 0; i < element_size; i++)
    //     *((uint8_t *)node->element + i) = *((uint8_t *)val + i);
    return node;
}

bool ll_append_tail(LinkedList *list, void *val, size_t size_element) {
    if(!list || !val) return false;
    if(list->element_size != size_element) return false;
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

bool ll_append_head(LinkedList *list, void *val, size_t size_element) {
    if(!list || !val) return false;
    if(list->element_size != size_element) return false;
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

void *ll_remove_tail(LinkedList *list) {
    if(!list) return NULL;
    if(!list->head) return NULL;
    if(list->head == list->tail) {
        void *head = list->head->element;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->len--;
        return head;
    }
    LLNode *tail = list->tail;
    tail->before->next = list->head;
    list->head->before = tail->before;
    list->tail = tail->before;
    void *val = tail->element;
    free(tail);
    list->len--;
    return val;
}

void *ll_remove_head(LinkedList *list) {
    if(!list) return NULL;
    if(!list->head) return NULL;
    if(list->head == list->tail) {
        void *head = list->head->element;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->len--;
        return head;
    }
    LLNode *head = list->head;
    head->next->before = list->tail;
    list->tail->next = head->next;
    list->head = head->next;
    void *val = head->element;
    free(head);
    list->len--;
    return val;
}

void *ll_remove_val(LinkedList *list, void *val) {
    LLNode *p = ll_get_node(list, val);
    if(!p) return NULL;
    LLNode *before = p->before;
    LLNode *next = p->next;
    before->next = next;
    next->before = before;
    if(p == list->head && p == list->tail) {
        void *val = p->element;
        list->head = NULL;
        list->tail = NULL;
        free(p);
        return val;
    }
    if(p == list->head)
        list->head = next;
    if(p == list->tail)
        list->tail = before;
    void *retval = p->element;
    free(p);
    list->len--;
    return retval;
}

void *ll_remove_at(LinkedList *list, size_t pos) {
    if(!list) return NULL;
    if(!list->head) return NULL;
    LLNode *p = list->head;
    for(size_t i = 0; i < pos; i++)
        p = p->next;
    return ll_remove_val(list, p->element);
}

LLNode *ll_get_node(LinkedList *list, void *val) {
    if(!list || !val) return NULL;
    if(!list->head) return NULL;
    LLNode *p = list->head;
    do {
        if(memcmp(p->element, val, list->element_size) == 0) return p;
        // for(size_t i = 0; i < list->element_size; i++)
        //     if(*((uint8_t*)p->element + i) != *((uint8_t*)val + i)) found = false;
        p = p->next;
    } while(p != list->head);
    return NULL;
}

LLNode *ll_get_node_at(LinkedList *list, size_t pos) {
    if(pos == 0) return list->head;
    if(pos == list->len - 1) return list->tail;
    size_t count = 1;
    LLNode *p = list->head;
    for(size_t i = 0; i < pos; i++)
        p = p->next;
    return p;
}

void ll_free(LinkedList *list) {
    if(!list) return;
    if(!list->head) {
        free(list);
        return;
    }
    LLNode *head = list->head;
    LLNode *p = head;
    do {
        free(p->element);
        LLNode *next = p->next;
        free(p);
        p = next;
    } while(p != head);
    free(list);
}
