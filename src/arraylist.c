#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <arraylist.h>

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

bool al_input_unsafe(ArrayList *list, void *new_element, size_t element_size, size_t position) {
    if(!list || !new_element) return false;
    if(element_size != list->size_elements) return false;
    if(position >= list->len) return false;
    
    uint8_t *dest = (uint8_t *)list->elements + (list->size_elements * position);
    memmove(dest, (uint8_t *)new_element, list->size_elements);
    return true;
}

bool al_add(ArrayList *list, void *new_element, size_t element_size) {
    if(!list || !new_element) return false;
    if(element_size != list->size_elements) return false;
    if(list->count == list->len)
        if(!al_realloc(list)) return false;
    
    uint8_t *dest = (uint8_t *)list->elements + (list->size_elements * list->count);
    memmove(dest, new_element, list->size_elements);
    list->count += 1;
    return true;
}

bool al_add_at(ArrayList *list, void *new_element, size_t element_size, size_t pos) {
    if(!list || !new_element) return false;
    if(element_size != list->size_elements) return false;
	if(list->count == list->len)
        if(!al_realloc(list)) return false;
    if(list->count <= pos) return al_add(list, new_element, element_size);
	memmove((uint8_t*)list->elements + (list->size_elements * (pos + 1)),
			(uint8_t*)list->elements + (list->size_elements * pos),
			list->size_elements * (list->count - pos));
    memmove((uint8_t*)list->elements + (list->size_elements * pos), new_element, list->size_elements);
    list->count += 1;
    return true;
}

bool al_add_many(ArrayList *list, void *elements, size_t elements_count, size_t elements_size) {
    if(!list || !elements) return false;
    if(elements_size != list->size_elements) return false;
    if(list->count + elements_count >= list->len) {
        while(list->len < list->count + elements_count) {
            void *check = realloc(list->elements, list->size_elements * list->len * 2);
            if(!check) return false;
            list->elements = check;
            list->len *= 2;
        }
    }
	memmove((uint8_t*)list->elements + (list->count * list->size_elements), elements, elements_size);
	list->count += elements_count;
    return true;
}

bool al_add_many_at(ArrayList *list, void *elements, size_t elements_count, size_t elements_size, size_t pos) {
	if(!list || !elements) return false;
	if(elements_size != list->size_elements) return false;
	if(list->count <= pos) return al_add_many(list, elements, elements_count, elements_size);
	if(!list->count + elements_count >= list->len) {
        while(list->len < list->count + elements_count) {
            void *check = realloc(list->elements, list->size_elements * list->len * 2);
            if(!check) return false;
            list->elements = check;
            list->len *= 2;
        }
	}
	memmove((uint8_t*)list->elements + ((pos + elements_count) * elements_size),
			(uint8_t*)list->elements + (pos * element_size),
			element_size * elements_count);
	memmove((uint8_t*)list->elements + (pos * element_size),
			elements,
			element_size * elements_count);
	list->count += elements_count;
	return true;
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
    if(al_has(list, val, element_size, &pos)) {
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
