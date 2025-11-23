<<<<<<< HEAD:src/arraylist.c
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <arraylist.h>

//TODO: err_handling

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

ArrayList *al_alloc() {
    ArrayList *list = calloc(1, sizeof(*list));
    return list;
}

ArrayList *al_create(size_t element_size) {
    ArrayList *list = al_create_array_list();
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

ArrayList *al_alloc_array_list_sized(size_t element_size, size_t len) {
    ArrayList *list = al_create_array_list();
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

bool al_realloc_array_list(ArrayList *list) {
    if(!list) return false;
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
    
    void *dest = list->elements + (list->size_elements * position);
    for(size_t i = 0; i < list->size_elements; i++)
        memmove(dest, new_element, list->size_elements);
        // *((uint8_t *)list->elements + i + (list->size_elements * position)) = *(i + (uint8_t *)new_element);
    return true;
}

bool al_append_element(ArrayList *list, void *new_element, size_t element_size) {
    if(!list || !new_element) return false;
    if(element_size != list->size_elements) return false;
    if(list->count == list->len)
        if(!al_realloc_array_list(list)) return false;
    //if you want to use pointers like int *a, you'd still need to pass as a ref &a
    
    void *dest = list->elements + (list->size_elements * list->count);
    for(size_t i = 0; i < list->size_elements; i++)
        memmove(dest, new_element, list->size_elements);
        // *((uint8_t *)list->elements + i + (list->size_elements * list->count)) = *(i + (uint8_t *)new_element);
    list->count += 1;
    return true;
}

bool al_push(ArrayList *list, void *new_element, size_t element_size) {
    if(!list || !new_element) return false;
    if(element_size != list->size_elements) return false;
    if(list->count == list->len)
        if(!al_realloc_array_list(list)) return false;
    for(size_t i = list->count - 1; i > 0; i++) {
        void *src = list->elements + (i * list->size_elements);
        void *dest = list->elements + ((i + 1) * list->size_elements);
        memmove(dest, src, list->size_elements);
    }
    // for(size_t j = 0; j < list->size_elements; j++)
    //     *((uint8_t*)list->elements + i + j + 1) = *((uint8_t*)list->elements + i + j);
    memmove(list->elements, new_element, list->size_elements);
    // for(size_t i = 0; i < list->size_elements; i++)
    //     *((uint8_t *)list->elements + i) = *(i + (uint8_t *)new_element);
    list->count += 1;
    return true;
}

bool al_append_many(ArrayList *list, void *elements, size_t elements_count, size_t elements_size) {
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
    for(size_t i = 0; i < elements_count; i++)
        al_append_element(list, (void *)(elements + (i * elements_size)), elements_size);
    return true;
}

ArrayList *al_copy_list(ArrayList *list) {
    if(!list) return NULL;
    ArrayList *cpy = al_alloc_array_list(list->size_elements);
    for(int i = 0; i < list->count; i++)
        al_append_element(cpy, (void*)(list->elements + (i * list->size_elements)), list->size_elements);
    return cpy;
}

ArrayList *al_concat_lists(ArrayList *l1, ArrayList *l2) {
    if(!l1 || !l2) return NULL;
    if(l1->size_elements != l2->size_elements) return NULL; //err check;
    ArrayList *lret = al_create_array_list();
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
    memmove(a, l2->elements, l2->count * l2->size_elements);
    // for(uint64_t j = 0; j < l1->size_elements * l1->count; j++)
    //     a[j] = *(j + (uint8_t*)l1->elements);
    // for(uint64_t j = 0; j < l2->size_elements * l2->count; j++)
    //     a[l1->count * l1->size_elements + j] = *(j + (uint8_t*)l2->elements);
    lret->elements = (void *)a;
    lret->size_elements = l1->size_elements;
    lret->count = n_size;
    lret->len = i;
    return lret;
}

bool al_is_array_list_empty(ArrayList *list) {
    return (list->count == 0);
}

bool al_has(ArrayList *list, void *val, size_t element_size, size_t *pos) {
    if(!list || !val) return false;
    if(list->size_elements != element_size) return false;
    for(size_t i = 0; i < list->count; i++) {
        bool found = true;
        void *s1 = list->elements + (i * list->size_elements);
        if(memcmp(s1, val, list->size_elements) != 0) 
            found = false;
        // for(size_t j = 0; j < list->size_elements; j++)
        //     *((uint8_t*)list->elements + j + (i*list->size_elements)) != *((uint8_t*)val + j)
        if(found) {
            *pos = i;
            return true;
        }
    }
    return false;
}

bool al_has_at(ArrayList *list, void *val, size_t element_size, size_t pos) {
    if(!list || !val) return false;
    if(list->size_elements != element_size) return false;
    if(list->count < pos) return false;
    bool found = true;
    void *s1 = list->elements + (pos * list->size_elements);
    if(memcmp(s1, val, list->size_elements) != 0) found = false;
    // for(size_t i = 0; i < list->size_elements; i++)
    //     if(*((uint8_t*)list->elements + i + (pos * list->size_elements)) != *((uint8_t*)val + i)) 
    //         found = false;
    return found;
}

void *al_get_ith(ArrayList *list, size_t i) {
    if(!list | i > list->len) return NULL;
    return list + (list->size_elements * i);
}

void *al_remove_at(ArrayList *list, size_t pos) {
    if(!list) return NULL;
    if(list->count == 0 || list->count <= pos) return NULL;
    void *element = malloc(list->size_elements);
    if(!element) return NULL;
    void *src = list->elements + (list->size_elements * pos);
    memmove(element, src, list->size_elements);
    // for(int i = 0; i < list->size_elements; i++) 
    //     *((uint8_t*)element + i) = *((uint8_t*)list->elements + (list->size_elements * pos) + i);
    for(int i = pos + 1; i < list->count; i++) {
        void *src = list->elements + (list->size_elements * i);
        void *dest = list->elements + (list->size_elements * (i - 1));
        memmove(dest, src, list->size_elements);
        // for(int j = 0; j < list->size_elements; j++)
        //     *((i-1) * list->size_elements + j + (uint8_t*)list->elements) = *(i * list->size_elements + j + (uint8_t*)list->elements);
    }
    list->count--;
    return element;
}

void *al_pop(ArrayList *list) {
    return al_remove_at(list, 0);
}

void *al_dequeue(ArrayList *list) {
    return al_remove_at(list, list->count-1);
}

bool al_remove_val(ArrayList *list, void *val, size_t element_size) {
    if(!list) return false;
    if(!val) return false;
    if(list->size_elements != element_size) return false;
    size_t pos = 0;
    if(al_has(list, val, element_size, &pos)) {
        void *v = al_remove_at(list, pos);
        free(v);
        return true;
    }
    return false;
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
=======
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "arraylist.h"

//TODO: err_handling

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

ArrayList *al_create_array_list() {
    ArrayList *list = calloc(1, sizeof(*list));
    return list;
}

ArrayList *al_alloc_array_list(size_t element_size) {
    ArrayList *list = al_create_array_list();
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

ArrayList *al_alloc_array_list_sized(size_t element_size, size_t len) {
    ArrayList *list = al_create_array_list();
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

bool al_realloc_array_list(ArrayList *list) {
    if(!list) return false;
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
    
    void *dest = list->elements + (list->size_elements * position);
    for(size_t i = 0; i < list->size_elements; i++)
        memmove(dest, new_element, list->size_elements);
        // *((uint8_t *)list->elements + i + (list->size_elements * position)) = *(i + (uint8_t *)new_element);
    return true;
}

bool al_append_element(ArrayList *list, void *new_element, size_t element_size) {
    if(!list || !new_element) return false;
    if(element_size != list->size_elements) return false;
    if(list->count == list->len)
        if(!al_realloc_array_list(list)) return false;
    //if you want to use pointers like int *a, you'd still need to pass as a ref &a
    
    void *dest = list->elements + (list->size_elements * list->count);
    for(size_t i = 0; i < list->size_elements; i++)
        memmove(dest, new_element, list->size_elements);
        // *((uint8_t *)list->elements + i + (list->size_elements * list->count)) = *(i + (uint8_t *)new_element);
    list->count += 1;
    return true;
}

bool al_push(ArrayList *list, void *new_element, size_t element_size) {
    if(!list || !new_element) return false;
    if(element_size != list->size_elements) return false;
    if(list->count == list->len)
        if(!al_realloc_array_list(list)) return false;
    for(size_t i = list->count - 1; i > 0; i++) {
        void *src = list->elements + (i * list->size_elements);
        void *dest = list->elements + ((i + 1) * list->size_elements);
        memmove(dest, src, list->size_elements);
    }
    // for(size_t j = 0; j < list->size_elements; j++)
    //     *((uint8_t*)list->elements + i + j + 1) = *((uint8_t*)list->elements + i + j);
    memmove(list->elements, new_element, list->size_elements);
    // for(size_t i = 0; i < list->size_elements; i++)
    //     *((uint8_t *)list->elements + i) = *(i + (uint8_t *)new_element);
    list->count += 1;
    return true;
}

bool al_append_many(ArrayList *list, void *elements, size_t elements_count, size_t elements_size) {
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
    for(size_t i = 0; i < elements_count; i++)
        al_append_element(list, (void *)(elements + (i * elements_size)), elements_size);
    return true;
}

ArrayList *al_copy_list(ArrayList *list) {
    if(!list) return NULL;
    ArrayList *cpy = al_alloc_array_list(list->size_elements);
    for(int i = 0; i < list->count; i++)
        al_append_element(cpy, (void*)(list->elements + (i * list->size_elements)), list->size_elements);
    return cpy;
}

ArrayList *al_concat_lists(ArrayList *l1, ArrayList *l2) {
    if(!l1 || !l2) return NULL;
    if(l1->size_elements != l2->size_elements) return NULL; //err check;
    ArrayList *lret = al_create_array_list();
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
    memmove(a, l2->elements, l2->count * l2->size_elements);
    // for(uint64_t j = 0; j < l1->size_elements * l1->count; j++)
    //     a[j] = *(j + (uint8_t*)l1->elements);
    // for(uint64_t j = 0; j < l2->size_elements * l2->count; j++)
    //     a[l1->count * l1->size_elements + j] = *(j + (uint8_t*)l2->elements);
    lret->elements = (void *)a;
    lret->size_elements = l1->size_elements;
    lret->count = n_size;
    lret->len = i;
    return lret;
}

bool al_is_array_list_empty(ArrayList *list) {
    return (list->count == 0);
}

bool al_has(ArrayList *list, void *val, size_t element_size, size_t *pos) {
    if(!list || !val) return false;
    if(list->size_elements != element_size) return false;
    for(size_t i = 0; i < list->count; i++) {
        bool found = true;
        void *s1 = list->elements + (i * list->size_elements);
        if(memcmp(s1, val, list->size_elements) != 0) 
            found = false;
        // for(size_t j = 0; j < list->size_elements; j++)
        //     *((uint8_t*)list->elements + j + (i*list->size_elements)) != *((uint8_t*)val + j)
        if(found) {
            *pos = i;
            return true;
        }
    }
    return false;
}

bool al_has_at(ArrayList *list, void *val, size_t element_size, size_t pos) {
    if(!list || !val) return false;
    if(list->size_elements != element_size) return false;
    if(list->count < pos) return false;
    bool found = true;
    void *s1 = list->elements + (pos * list->size_elements);
    if(memcmp(s1, val, list->size_elements) != 0) found = false;
    // for(size_t i = 0; i < list->size_elements; i++)
    //     if(*((uint8_t*)list->elements + i + (pos * list->size_elements)) != *((uint8_t*)val + i)) 
    //         found = false;
    return found;
}

void *al_get_ith(ArrayList *list, size_t i) {
    if(!list || i > list->len) return NULL;
    return list + (list->size_elements * i);
}

void *al_remove_at(ArrayList *list, size_t pos) {
    if(!list) return NULL;
    if(list->count == 0 || list->count <= pos) return NULL;
    void *element = malloc(list->size_elements);
    if(!element) return NULL;
    void *src = list->elements + (list->size_elements * pos);
    memmove(element, src, list->size_elements);
    // for(int i = 0; i < list->size_elements; i++) 
    //     *((uint8_t*)element + i) = *((uint8_t*)list->elements + (list->size_elements * pos) + i);
    for(int i = pos + 1; i < list->count; i++) {
        void *src = list->elements + (list->size_elements * i);
        void *dest = list->elements + (list->size_elements * (i - 1));
        memmove(dest, src, list->size_elements);
        // for(int j = 0; j < list->size_elements; j++)
        //     *((i-1) * list->size_elements + j + (uint8_t*)list->elements) = *(i * list->size_elements + j + (uint8_t*)list->elements);
    }
    list->count--;
    return element;
}

void *al_pop(ArrayList *list) {
    return al_remove_at(list, 0);
}

void *al_dequeue(ArrayList *list) {
    return al_remove_at(list, list->count-1);
}

bool al_remove_val(ArrayList *list, void *val, size_t element_size) {
    if(!list) return false;
    if(!val) return false;
    if(list->size_elements != element_size) return false;
    size_t pos = 0;
    if(al_has(list, val, element_size, &pos)) {
        void *v = al_remove_at(list, pos);
        free(v);
        return true;
    }
    return false;
}

bool al_free_array_list(ArrayList *list) {
    if(!list) return true; //it's effectively already freed
    free(list->elements);
    list->elements = NULL;
    list->len = 0;
    list->size_elements = 0;
    free(list);
    return true;
}
>>>>>>> d08a5d5df234869e3cb60b3b662f9a323004031c:arraylist/arraylist.c
