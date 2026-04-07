#include <stdlib.h>
#include <hashmap.h>

HashMap *hm_create(size_t size_key, size_t size_value) {
	return hm_create_full(size_key, size_value, NULL, NULL, NULL, NULL);
}

void _hmp_destroy(void *element) {
	HashMapPair *hmp = element;
	free(hmp->key);
	free(hmp->value);
}

HashMap *hm_create_full(size_t size_key, size_t size_value, compare_fn compare_key, compare_fn compare_value, destroy_fn destroy_key, destroy_fn destroy_value) {
	HashMap *hm = malloc(sizeof(*hm));
	if(!hm) return NULL;
	hm->hs = hs_create(sizeof(HashMapPair));
	if(!(hm->hs)) {
		free(hm);
		return NULL;
	}
	hs_change_destroyer(hm->hs, _hmp_destroy);
	hm->size_key = size_key;
	hm->size_value = size_value;
	
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
	HashMapPair new_entry = {0};
	new_entry.key = malloc(hm->size_key);
	new_entry.value = malloc(hm->size_value);
	if(!new_entry.key || !new_entry.value) {
		if(new_entry.key) free(new_entry.key);
		if(new_entry.value) free(new_entry.value);
		return false;
	}
	memcpy(new_entry.key, key, hm->size_key);
	memcpy(new_entry.value, value, hm->size_value);
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
	if(hs_add_val(hm->hs, &new_entry, pos)) hm->hs->count++;
	if(hs_load_factor(hm->hs) > HS_MAX_LOAD_FACTOR) return hs_rehash(hm->hs);
	return true;
}

bool hm_has_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
    LinkedList *ll = *(LinkedList**)al_get_ith(hm->hs->list, pos);
	if(!ll) return false;
	LLNode *head = ll->head;
	if(!head) return false;
	LLNode *p = head;
	int res = 0;
	do {
		HashMapPair *hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->size_key);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return true;
	return false;
}

bool hm_has_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	bool found = false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->count; i++) {
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		int res = 0;
		do {
			HashMapPair *hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->size_value);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) found = true;
		if(found) break;
	}
	return found;
}

void*hm_get_value(HashMap *hm, void *key) {
	if(!hm || !key) return NULL;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
    LinkedList *ll = *(LinkedList**)al_get_ith(hm->hs->list, pos);
	if(!ll) return NULL;
	LLNode *head = ll->head;
	if(!head) return NULL;
	LLNode *p = head;
	HashMapPair *hmp;
	int res = 0;
	do {
		hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->size_key);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) return hmp->value;
	return NULL;
}

void*hm_get_key(HashMap *hm, void *value) {
	if(!hm || !value) return NULL;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->count; i++) {
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		int res = 0;
		do {
			hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->size_value);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) return hmp->key;
	}
	return NULL;
}

bool hm_remove_key(HashMap *hm, void *key) {
	if(!hm || !key) return false;
	size_t pos = hs_hash_val(hm->hs, key, hm->size_key);
    LinkedList *ll = *(LinkedList**)al_get_ith(hm->hs->list, pos);
	if(!ll) return false;
	LLNode *head = ll->head;
	if(!head) return false;
	LLNode *p = head;
	HashMapPair *hmp;
	int res = 0;
	do {
		hmp = p->element;
		res = hm->compare_key(hmp->key, key, hm->size_key);
		p = p->next;
	} while(res != 0 && p != head); 
	if(res == 0) {
	    if(hm->destroy_key) hm->destroy_key(hmp->key);
	    if(hm->destroy_value) hm->destroy_value(hmp->value);
	
	    free(hmp->key);
	    free(hmp->value);
	
	    return ll_remove_val(ll, hmp);
	}
	return false;
}

bool hm_remove_value(HashMap *hm, void *value) {
	if(!hm || !value) return false;
	ArrayList *list = hm->hs->list;
	for(size_t i = 0; i < list->count; i++) {
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
		LLNode *head = ll->head;
		if(!head) continue;
		LLNode *p = head;
		HashMapPair *hmp;
		int res = 0;
		do {
			hmp = p->element;
			res = hm->compare_value(hmp->value, value, hm->size_value);
			p = p->next;
		} while(res != 0 && p != head);
		if(res == 0) {
   			if(hm->destroy_key) hm->destroy_key(hmp->key);
		    if(hm->destroy_value) hm->destroy_value(hmp->value);
		
		    free(hmp->key);
		    free(hmp->value);
		
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
	size_t counting = (list->count * sizeof(LinkedList*)) + (hm->hs->count * (sizeof(HashMapPair) + hm->size_key + hm->size_value));
	for(size_t i = 0; i < list->count; i++) {
		LinkedList *ll = ((LinkedList**)(list->elements))[i];
		if(!ll) continue;
		structs += sizeof(LinkedList);
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
	for(size_t i = 0; i < (*hm)->hs->list->len; i++) {
		LinkedList *ll = ((LinkedList**)((*hm)->hs->list->elements))[i];
		if(!ll) continue;
		LLNode *p = ll->head;
		do {
			HashMapPair* element = p->element;
			if((*hm)->destroy_key) (*hm)->destroy_key(element->key);
			if((*hm)->destroy_value) (*hm)->destroy_value(element->value);
			p = p->next;
		} while(p != ll->head);
	}
	if(!hs_destroy(&((*hm)->hs))) return false;
	free(*hm);
	*hm = NULL;
	return true;
}

