#include <stdlib.h>
#include <hashmap.h>

HashMap *hm_create(size_t size_key, size_t size_value) {
	HashMap *hm = malloc(sizeof(*hm));
}

bool hm_add(HashMap *hm, void *key, void *value);

bool hm_has_key(HashMap *hm, void *key);
bool hm_has_value(HashMap *hm, void *value); /*O(n) search*/
void*hm_get_value(HashMap *hm, void *key); /*basically doing hm[key] <- returns the pointer to value*/
void*hm_get_key(HashMap *hm, void *value); /*O(n) search */

bool hm_remove_key(HashMap *hm, void *key, void *out_ptr); /*returns value associated with key*/
bool hm_remove_value(HashMap *hm, void *value, void *out_ptr); /*return key associated with value, O(n) search*/

bool hm_is_empty(HashMap *hm);
size_t hm_size(HashMap *hm);

bool hm_destroy(HashMap **hm);
