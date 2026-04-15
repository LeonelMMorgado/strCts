#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#define INITIAL_ARRAY_CAPACITY 256

typedef struct _dynamic_array_header {
	size_t len;
	size_t count;
} ArrayHeader;

#define array_create(array) \
	do { \
		ArrayHeader *h = malloc(sizeof(ArrayHeader) + (sizeof(*(array)) * INITIAL_ARRAY_CAPACITY)); \
		h->len = INITIAL_ARRAY_CAPACITY; \
		h->count = 0; \
		(array) = (void*)(h + 1); \
	} while(0)

#define array_create_sized(array, size) \
	do { \
		ArrayHeader *h = malloc(sizeof(ArrayHeader) + (sizeof(*(array)) * (size))); \
		h->len = (size); \
		h->count = 0; \
		(array) = (void*)(h + 1); \
	} while(0)

#define array_input_unsafe(array, x, pos) (array)[(pos)] = (x)

#define array_add(array, x) \
	do { \
		if(!(array)) { \
			array_create((array)); \
		} \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		if(h->count == h->len) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		(array)[h->count++] = (x); \
	} while(0)

#define array_push(array, x) array_add((array), (x))

#define array_add_at(array, x, pos) \
	do { \
		if(!(array)) array_create((array)); \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		if(h->count == h->len) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		memmove((array) + (pos) + 1, (array) + (pos), sizeof(*(array)) * (h->count - pos)); \
		(array)[(pos)] = (x); \
		h->count++; \
	} while(0)

#define array_add_many(array, elements, elements_count) \
	do { \
		if(!(array)) array_create((array)); \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		while(h->len - h->count < elements_count) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		memmove((array) + h->count, elements, elements_count * sizeof(*(array))); \
		h->count += elements_count; \
	} while(0)

#define array_add_many_at(array, elements, elements_count, pos) \
	do { \
		if(!(array)) array_create((array)); \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		while(h->len - h->count < elements_count) { \
			void *check = realloc(h, sizeof(ArrayHeader) + sizeof(*(array)) * h->len * 2); \
			if(check) { \
				h = check; \
				(array) = (void*)(h + 1); \
				h->len *= 2; \
			} \
		} \
		memmove((array) + (pos) + elements_count, (array) + (pos), (h->count - (pos)) * sizeof(*(array))); \
		memmove((array) + (pos), (elements), elements_count * sizeof(*(array))); \
		h->count += elements_count; \
	} while(0)

#define array_update(array, update, pos) array_input_unsafe((array), (update), (pos))

#define array_copy(array, new_array) \
	do { \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		array_add_many((new_array), (array), h->count); \
	} while(0)

#define array_concat(array1, array2) \
	do { \
		ArrayHeader *h2 = ((ArrayHeader*)(array2)) - 1; \
		array_add_many((array1), (array2), h2->count); \
	} while(0)

#define array_concat_new(array1, array2, arrayret) \
	do { \
		if(!(arrayret)) array_create((arrayret)); \
		ArrayHeader *h1 = ((ArrayHeader*)(array1)) - 1; \
		ArrayHeader *h2 = ((ArrayHeader*)(array2)) - 1; \
		array_add_many((arrayret), (array1), h1->count); \
		array_add_many((arrayret), (array2), h2->count); \
	} while(0)

//pos is a return argument
#define array_has(array, val, pos) \
	({ \
	 	bool found = false; \
		ArrayHeader *h = ((ArrayHeader*)(array)) - 1; \
		for(size_t i = 0; i < h->count; i++) { \
			if((array)[i] == (val)) { \
				*(pos) = i; \
	 			found = true; \
			} \
			if(found) break; \
		} \
		found; \
	})

#define array_has_at(array, val, pos) memcmp((array) + (pos), (val), sizeof(*(array))) == 0

#define array_size(array) (((ArrayHeader*)(array)) - 1)->count

#define array_is_empty(array) (array_size((array)) == 0)

#define array_remove_at(array, pos, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if((out_ptr)) *(typeof((array)))(out_ptr) = (array)[(pos)]; \
		memmove((array) + (pos), (array) + (pos) + 1, sizeof(*(array)) * (h->count - (pos) - 1)); \
		h->count -= 1; \
	} while(0)

//changes array order
#define array_remove_at_fast(array, pos, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if((out_ptr)) *(typeof((array)))(out_ptr) = (array)[(pos)]; \
		(array)[(pos)] = (array)[h->count - 1]; \
		h->count -= 1; \
	} while(0)

#define array_pop(array, out_ptr) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		if((out_ptr)) *(typeof((array)))(out_ptr) = (array)[h->count - 1]; \
		h->count -= 1; \
	} while(0)

#define array_remove_first(array, out_ptr) array_remove_at((array), 0, (out_ptr))

#define array_remove_val(array, val) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		for(size_t i = 0; i < h->count; i++) { \
			if((array)[i] == val) { \
	 			array_remove_at((array), i, NULL); \
			} \
		} \
	} while(0)

#define array_clear(array) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		for(size_t i = 0; i < h->count; i++) { \
			(array)[i] = 0; \
		} \
		h->count = 0; \
	} while(0)

#define array_fit(array) \
	do { \
		ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
		h = realloc(h, sizeof(ArrayHeader) + (h->count * sizeof(*(array)))); \
		h->len = h->count; \
		(array) = (void*)(h + 1); \
	} while(0)

#define array_destroy(array) \
	do { \
		if((array)) { \
			ArrayHeader *h = (((ArrayHeader*)(array)) - 1); \
			free(h); \
			(array) = NULL; \
		} \
	} while(0)

#endif

