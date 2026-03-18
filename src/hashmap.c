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

HashMap *hm_create(size_t size_key, size_t size_value) {
	HashMap *hm = malloc(sizeof(*hm));
	if(!hm) return NULL;
	hm->hs = hs_create(sizeof(HashMapPair));
	if(!(hm->hs)) {
		free(hm);
		return NULL;
	}
	hm->key_size = size_key;
	hm->value_size = size_value;
	return hm;
}

bool hm_add(HashMap *hm, void *key, void *value) {
	if(!hm || !key || !value) return false;
	if(hm_has_key(hm, key)) { //could return position?
		if(memcmp(hm_get_value(hm, key), value, hm->size_value) == 0) 
			return false;
	HashMapPair *new_entry = _hmp_create(key, value, hm->size_key, hm->size_value);
	if(!new_entry) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
	if(hs_add_val(hm->hs, new_entry, hs_hash_val(hm->hs, key, hm->size_key))) hm->hs->count++;
	if(hs_load_factor(hm->hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hm->hs);
	return true;
}

bool hm_has_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm-size_key);
    HashEntry*ith = (HashEntry*)al_get_ith(hs->list, position);
	if(!(ith->valid_entry)) return false;
	if(!(ith->elements)) return false;
	LinkedList *ll = ith->elements;
	LLNode *head = ll->head;
	if(!head) return false;
	LLNode *p = head;
	do {
		HashMapPair *hmp = p->val;
		int res = memcmp(hmp->key, key, hm->size_key);
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
		if(entr.valid_entry == false) continue
		if(entry.elements == NULL) continue;
		LinkedList *ll = entry.elements;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		do {
			HashMapPair *hmp = p->val;
			int res = memcmp(hmp->key, key, hm->size_key);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) found = true;
		if(found) break;
	}
	return found;
}

void*hm_get_value(HashMap *hm, void *key) {
	if(!hm || !key) return NULL;
	size_t pos = hs_hash_val(hm->hs, key, hm-size_key);
    HashEntry*ith = (HashEntry*)al_get_ith(hs->list, position);
	if(!(ith->valid_entry)) return NULL;
	if(!(ith->elements)) return NULL;
	LinkedList *ll = ith->elements;
	LLNode *head = ll->head;
	if(!head) return NULL;
	LLNode *p = head;
	HashMapPair *hmp;
	do {
		hmp = p->val;
		int res = memcmp(hmp->key, key, hm->size_key);
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
		if(entr.valid_entry == false) continue
		if(entry.elements == NULL) continue;
		LinkedList *ll = entry.elements;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		do {
			hmp = p->val;
			int res = memcmp(hmp->key, key, hm->size_key);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) return hmp->key;
	}
	return NULL;
}

bool hm_remove_key(HashMap *hm, void *key, void *out_ptr) {
	if(!hm || !key) return NULL;
	size_t pos = hs_hash_val(hm->hs, key, hm-size_key);
    HashEntry*ith = (HashEntry*)al_get_ith(hs->list, position);
	if(!(ith->valid_entry)) return NULL;
	if(!(ith->elements)) return NULL;
	LinkedList *ll = ith->elements;
	LLNode *head = ll->head;
	if(!head) return NULL;
	LLNode *p = head;
	HashMapPair *hmp;
	do {
		hmp = p->val;
		int res = memcmp(hmp->key, key, hm->size_key);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) {
		*out_ptr = hmp->val;
		ll_remove_value(ll, hmp);
	}
	return NULL;
}

bool hm_remove_value(HashMap *hm, void *value, void *out_ptr) {
	if(!hm || !value) return NULL;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->len; i++) {
		HashEntry entry = ((HashEntry*)(list->elements))[i];
		if(entr.valid_entry == false) continue
		if(entry.elements == NULL) continue;
		LinkedList *ll = entry.elements;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		do {
			hmp = p->val;
			int res = memcmp(hmp->key, key, hm->size_key);
			p = p->next;
		} while(res != 0 && p != head);
		ll_remove_value(ll, hmp);
	}
	return NULL;
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
	size_t counting = (list->len * sizeof(HashEntry)) + (hm->hs->count * (sizeof(HashMapPair) + hm->size_key + hm->size_value));
	for(size_t i = 0; i < list->len; i++) {
		HashEntry *ith = ((HashEntry*)(list->elements))[i];
		if(ith.valid_entry == false) continue;
		if(ith.elements == NULL) continue;
		structs += sizeof(LinkedList);
		LinkedList *ll = entry.elements;
		LLNode *head = ll->head;
		LLNode *p = head;
		do {
			structs += sizeof(LLNode);
			p = p->head;
		} while(p != head);
	}
	total += structs + counting;
	if(total < counting || total < structs) return ~((size_t)0);//size_t max
	return total;
}

bool hm_destroy(HashMap **hm) {
	if(!hm || !*hm) return false;
	if(!hs_destroy(&((*hm)->hs))) return false;
	free(*hm);
	*hm = NULL;
	return true;
}
