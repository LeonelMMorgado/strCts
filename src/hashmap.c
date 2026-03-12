#include <stdlib.h>
#include <hashmap.h>

HashMap *hm_create(size_t size_key, size_t size_value) {
	HashMap *hm = malloc(sizeof(*hm));
	if(!hm) return NULL;
	hm->hs = hm_create(sizeof(HashMapPair));
	if(!(hm->hs)) {
		free(hm);
		return NULL;
	}
	hm->key_size = size_key;
	hm->value_size = size_value;
	return hm;
}

bool hm_add(HashMap *hm, void *key, void *value) {

}

bool hm_has_key(HashMap *hm, void *key) {

}

bool hm_has_value(HashMap *hm, void *value) {

}

void*hm_get_value(HashMap *hm, void *key) {

}

void*hm_get_key(HashMap *hm, void *value) {

}

bool hm_remove_key(HashMap *hm, void *key, void *out_ptr) {

}

bool hm_remove_value(HashMap *hm, void *value, void *out_ptr) {

}

bool hm_is_empty(HashMap *hm) {

}

size_t hm_size(HashMap *hm) {

}

bool hm_destroy(HashMap **hm) {

}
