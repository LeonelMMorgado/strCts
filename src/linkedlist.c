#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <linkedlist.h>

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

