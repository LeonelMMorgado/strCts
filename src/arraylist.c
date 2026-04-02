#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <arraylist.h>

ArrayList *al_alloc() {
    ArrayList *list = calloc(1, sizeof(*list));
    return list;
}

ArrayList *al_create(size_t element_size, compare_fn compare_function, destroy_fn destroy_function) {
    ArrayList *list = al_alloc();
    if(!list) return NULL;
    list->elements = calloc(256, element_size);
    if(!(list->elements)) {
        free(list);
        return NULL;
    }
    list->len = 256;
    list->size_elements = element_size;
	if(compare_function) list->compare_function = compare_function;
	else list->compare_function = &memcmp;
	list->destroy_function = destroy_function;
    return list;
}

ArrayList *al_create_sized(size_t element_size, size_t len, compare_fn compare_function, destroy_fn destroy_function) {
    ArrayList *list = al_alloc();
    if(!list) return NULL;
    list->elements = calloc(len, element_size);
    if(!(list->elements)) {
        free(list);
        return NULL;
    }
    list->len = len;
    list->size_elements = element_size;
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
