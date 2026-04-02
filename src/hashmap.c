#include <stdlib.h>
#include <hashmap.h>

HashMapPair *_hmp_create(void *key, void *value, size_t size_key, size_t size_value) {
	HashMapPair *hmp = malloc(sizeof(*hmp));
	if(!hmp) return NULL;
	hmp->key = malloc(size_key);
	hmp->value = malloc(size_value);
	if(!(hmp->key) || !(hmp->value)) {
		free(hmp);
		if(hmp->key) free(hmp->key);
		if(hmp->value) free(hmp->value);
		return NULL;
	}
	memcpy(hmp->key, key, size_key);
	memcpy(hmp->value, value, size_value);
	return hmp;
}

HashMap *hm_create(size_t size_key, size_t size_value, compare_fn compare_key, compare_fn compare_value, destroy_fn destroy_key, destroy_fn destroy_value) {
	HashMap *hm = malloc(sizeof(*hm));
	if(!hm) return NULL;
	hm->hs = hs_create(sizeof(HashMapPair), NULL, NULL);
	if(!(hm->hs)) {
		free(hm);
		return NULL;
	}
	hm->key_size = size_key;
	hm->value_size = size_value;
	
	if(compare_key) hm->compare_key = compare_key;
	else hm->compare_key = &memcmp;
	if(compare_value) hm->compare_value = compare_value;
	else hm->compare_value = &memcmp;
	hm->destroy_key = destroy_key;
	hm->destroy_value = destroy_value;
	return hm;
}

bool hm_add(HashMap *hm, void *key, void *value) {
	if(!hm || !key || !value) return false;
	if(hm_has_key(hm, key)) return false;
	HashMapPair *new_entry = _hmp_create(key, value, hm->key_size, hm->value_size);
	if(!new_entry) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
	if(hs_add_val(hm->hs, new_entry, hs_hash_val(hm->hs, key, hm->key_size))) hm->hs->count++;
	if(hs_load_factor(hm->hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hm->hs);
	return true;
}

bool hm_has_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
    HashEntry*ith = (HashEntry*)al_get_ith(hm->hs->list, pos);
	if(!(ith->valid_entry)) return false;
	if(!(ith->element)) return false;
	LinkedList *ll = ith->element;
	LLNode *head = ll->head;
	if(!head) return false;
	LLNode *p = head;
	int res = 0;
	do {
		HashMapPair *hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->key_size);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return true;
	return false;
}

bool hm_has_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	bool found = false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->len; i++) {
		HashEntry entry = ((HashEntry*)(list->elements))[i];
		if(entry.valid_entry == false) continue;
		if(entry.element == NULL) continue;
		LinkedList *ll = entry.element;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		int res = 0;
		do {
			HashMapPair *hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->value_size);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) found = true;
		if(found) break;
	}
	return found;
}

void*hm_get_value(HashMap *hm, void *key) {
	if(!hm || !key) return NULL;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
    HashEntry*ith = (HashEntry*)al_get_ith(hm->hs->list, pos);
	if(!(ith->valid_entry)) return NULL;
	if(!(ith->element)) return NULL;
	LinkedList *ll = ith->element;
	LLNode *head = ll->head;
	if(!head) return NULL;
	LLNode *p = head;
	HashMapPair *hmp;
	int res = 0;
	do {
		hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->key_size);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return hmp->value;
	return NULL;
}

void*hm_get_key(HashMap *hm, void *value) {
	if(!hm || !value) return NULL;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->len; i++) {
		HashEntry entry = ((HashEntry*)(list->elements))[i];
		if(entry.valid_entry == false) continue;
		if(entry.element == NULL) continue;
		LinkedList *ll = entry.element;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		int res = 0;
		do {
			hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->value_size);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) return hmp->key;
	}
	return NULL;
}

bool hm_remove_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->key_size);
    HashEntry*ith = (HashEntry*)al_get_ith(hm->hs->list, pos);
	if(!(ith->valid_entry)) return false;
	if(!(ith->element)) return false;
	LinkedList *ll = ith->element;
	LLNode *head = ll->head;
	if(!head) return false;
	LLNode *p = head;
	HashMapPair *hmp;
	int res = 0;
	do {
		hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->key_size);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) {
		return ll_remove_val(ll, hmp);
	}
	return false;
}

bool hm_remove_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->len; i++) {
		HashEntry entry = ((HashEntry*)(list->elements))[i];
		if(entry.valid_entry == false) continue;
		if(entry.element == NULL) continue;
		LinkedList *ll = entry.element;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		int res = 0;
		do {
			hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->value_size);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) {
			return ll_remove_val(ll, hmp);
		}
	}
	return false;
}

bool hm_is_empty(HashMap *hm) {
	return hm_size(hm) == 0;
}

size_t hm_size(HashMap *hm) {
	if(!hm) return 0;
	return hm->hs->count;
}

size_t hm_struct_size(HashMap *hm) {
	if(!hm) return 0;
	ArrayList *list = hm->hs->list;
	size_t total = 0;
	size_t structs = sizeof(HashMap) + sizeof(HashSet) + sizeof(ArrayList);
	size_t counting = (list->len * sizeof(HashEntry)) + (hm->hs->count * (sizeof(HashMapPair) + hm->key_size + hm->value_size));
	for(size_t i = 0; i < list->len; i++) {
		HashEntry ith = ((HashEntry*)(list->elements))[i];
		if(ith.valid_entry == false) continue;
		if(ith.element == NULL) continue;
		structs += sizeof(LinkedList);
		LinkedList *ll = ith.element;
		LLNode *head = ll->head;
		LLNode *p = head;
		do {
			structs += sizeof(LLNode);
			p = p->next;
		} while(p != head);
	}
	total += structs + counting;
	if(total < counting || total < structs) return ~((size_t)0);//size_t max
	return total;
}

bool hm_destroy(HashMap **hm) {
	if(!hm || !*hm) return false;
	for(size_t i = 0; i < hm->hs->list->len; i++) {
		HashEntry ith = ((HashEntry*)(hm->hs->list->elements))[i];
		if(ith.valid_entry == false) continue;
		if(ith.element == NULL) continue;
		LinkedList *ll = ith.element;
		LLNode *p = ll->head;
		do {
			hm->destroy_key(((HashMapPair*)(p->element))->key);
			hm->destroy_value(((HashMapPair*)(p->element))->value);
		} while(p != head);
	}
	if(!hs_destroy(&((*hm)->hs))) return false;
	free(*hm);
	*hm = NULL;
	return true;
}

