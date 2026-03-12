#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <linkedlist.h>

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

bool ll_add_tail(LinkedList *list, void *val, size_t size_element) {
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

bool ll_add_head(LinkedList *list, void *val, size_t size_element) {
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

bool ll_add_at(LinkedList *list, void *val, size_t size_element, size_t pos) {
	if(!list || !val) return false;
	if(list->element_size != size_element) return false;
	if(pos == 0) return ll_append_head(list, val, size_element);
	if(pos == list->len - 1) return ll_append_tail(list, val, size_element);
	size_t i = 0;
	LLNode *p = list->head;
	while(p) {
		if(i == pos) break;
		p = p->next;
		i++;
	}
	p->before->next = ll_create_node(val, list->element_size);
	if(!(p->before->next) return false;
	p->before = p->before->next;
	list->len += 1;
	return true;
}

bool ll_add_many_at(LinkedList *list, void *elements, size_t elements_count, size_t element_size, size_t pos) {
	if(!list || !elements) return false;
	if(list->element_size != element_size) return false;
	LLNode *first = ll_create_node(elements, element_size);
	LLNode *last = first;
	for(size_t i = 1; i < elements_count; i++) {
		last->next = ll_create_node((uint8_t*)elements + (i * elements_size), elements_size);
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

bool ll_add_many(LinkedList *list, void *elements, size_t elements_count, size_t elements_size) {
	if(!list || !elements) return false;
	if(list->element_size != elements_size) return false;
	return ll_append_many_at(list, elements, elements_count, element_size, list->len);
}

LinkedList *ll_copy_list(LinkedList *list) {
	if(!list) return NULL;
	LinkedList *new_l = ll_create(list->element_size);
	if(!new_l) return NULL;
	LLNode *p = list->head;
	for(size_t i = 0; i < list->len; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_append_tail(new_l, p->element, list->element_size);
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
		ll_append_tail(new_l, p->element, list->element_size);
		p = p->next;
	}
	p = list2->head;
	for(size_t i = 0; i < list2->len; i++) {
		//FIXME: could run better by doing the logic in here and only updating whats necessary
		ll_append_tail(new_l, p->element, list->element_size);
		p = p->next;
	}
	return new_l;
}

bool ll_remove_tail(LinkedList *list, void *out_ptr) {
    if(!list) return NULL;
    if(!list->head) return NULL;
    if(list->head == list->tail) {
        void *head = list->head->element;
		if(out_ptr) out_ptr = head->element;
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
	if(out_ptr) out_ptr = tail->element;
    free(tail);
    list->len--;
    return true;
}

bool ll_remove_head(LinkedList *list, void *out_ptr) {
    if(!list) return false;
    if(!list->head) return false;
    if(list->head == list->tail) {
        void *head = list->head->element;
		if(out_ptr) out_ptr = head->element;
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
	if(out_ptr) out_ptr = head->element;
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
    free(p);
    list->len--;
    return true;
}

bool ll_remove_at(LinkedList *list, size_t pos, void *out_ptr) {
    if(!list) return NULL;
    if(!list->head) return NULL;
    LLNode *p = list->head;
    for(size_t i = 0; i < pos; i++)
        p = p->next;
    if(p == list->head && p == list->tail) {
        void *val = p->element;
        list->head = NULL;
        list->tail = NULL;
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
