#ifndef _MEMCLASS_H
#define _MEMCLASS_H

#include <stdint.h>
#include <stdbool.h>

typedef int (*compare_fn)(const void *val1, const void *val2, size_t element_size);
typedef void (*destroy_fn)(void *element);

int int_compare(const void *val1, const void *val2, size_t element_size);
int uint_compare(const void *val1, const void *val2, size_t element_size);
int i64_compare(const void *val1, const void *val2, size_t element_size);
int u64_compare(const void *val1, const void *val2, size_t element_size);
int float_compare(const void *val1, const void *val2, size_t element_size);
int double_compare(const void *val1, const void *val2, size_t element_size);
int string_compare(const void *val1, const void *val2, size_t element_size);

void pointer_destroy(void *element);

#endif //_MEMCLASS_H
