#include <memclass.h>

int int_compare(const void *val1, const void *val2, size_t element_size) {
	int v1 = *(int*)val1;
	int v2 = *(int*)val2;
	return (v1 > v2) - (v1 < v2);
}

int uint_compare(const void *val1, const void *val2, size_t element_size) {
	unsigned int v1 = *(unsigned int*)val1;
	unsigned int v2 = *(unsigned int*)val2;
	return (v1 > v2) - (v1 < v2);
}

int i64_compare(const void *val1, const void *val2, size_t element_size) {
	int64_t v1 = *(int64_t*)val1;
	int64_t v2 = *(int64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int u64_compare(const void *val1, const void *val2, size_t element_size) {
	uint64_t v1 = *(uint64_t*)val1;
	uint64_t v2 = *(uint64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int float_compare(const void *val1, const void *val2, size_t element_size) {
	float v1 = *(float*)val1;
	float v2 = *(float*)val2;
	return (v1 > v2) - (v1 < v2);
}

int double_compare(const void *val1, const void *val2, size_t element_size) {
	double v1 = *(double*)val1;
	double v2 = *(double*)val2;
	return (v1 > v2) - (v1 < v2);
}

int string_compare(const void *val1, const void *val2, size_t element_size) {
	char *s1 = *(char**)val1;
	char *s2 = *(char**)val2;
	return strcmp(s1, s2);
}

void pointer_destroy(void *val) {
	if(!val) return;
	free(*(void **)val);
}
