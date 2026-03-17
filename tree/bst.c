/*
example usage:
int a = 0;
BSTree *root = bst_create(&a, sizeof(int));
for(int i = 0; i < 10; i++) {
	int rndn = rand();
	bst_insert(&root, &rndn);
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define bst_insert_const(bst, val, type) \
	do {\
		type var = (val);\
		bst_insert(&(bst), &var);\
	} while(0)

#define bst_remove_const(bst, val, type) \
	do {\
		type var = (val);\
		bst_remove(&(bst), &var);\
	} while(0)

typedef struct _tree_node {
    void *val;
    size_t size_element;
    struct _tree_node *left;
    struct _tree_node *right;
	int64_t height;
} BSTree;

int64_t _bst_max_impl(int64_t a, int64_t b) {
	return a > b ? a : b;
}

void bst_delete(BSTree **root);

BSTree *bst_create(void *val, size_t element_size) {
    BSTree *n = malloc(sizeof(*n));
	if(!n) return NULL;
		n->size_element = element_size;
    n->val = calloc(1, element_size);
	if(!(n->val)) return n;
    memcpy(n->val, val, element_size);
	n->left = NULL;
	n->right = NULL;
	n->height = 0;
	return n;
}

int64_t bst_height(BSTree *root) {
	if(!root) return -1;
	return root->height;
}

void _bst_update_height(BSTree *root) {
	root->height =_bst_max_impl(bst_height(root->left), bst_height(root->right)) + 1;
}

int64_t bst_balance(BSTree *root) {
	if(!root) return 0;
	return bst_height(root->left) - bst_height(root->right);
}

bool bst_is_balanced(BSTree *root) {
	int64_t balance_factor = bst_balance(root);
	return !(balance_factor < -1 || balance_factor > 1);
}

BSTree *_bst_rotate_left(BSTree *root) {
	if(!root) return NULL;
	if(!(root->right)) return NULL;
	BSTree *right = root->right;
	BSTree *rl = right->left;

	right->left = root;
	root->right = rl;

	_bst_update_height(root);
	_bst_update_height(right);

	return right;
}

BSTree *_bst_rotate_right(BSTree *root) {
	if(!root) return NULL;
	if(!(root->left)) return NULL;
	BSTree *left = root->left;
	BSTree *lr = left->right;

	left->right = root;
	root->left = lr;

	_bst_update_height(root);
	_bst_update_height(left);

	return left;
}

BSTree *_bst_rebalance(BSTree *root) {
	int64_t factor = bst_balance(root);

	if(factor > 1) {
		if(bst_balance(root->left) < 0)
			root->left = _bst_rotate_left(root->left);
		return _bst_rotate_right(root);
	}
	if(factor < -1) {
		if(bst_balance(root->right) > 0)
			root->right = _bst_rotate_right(root->right);
    	return _bst_rotate_left(root);
	}

	return root;
}

//FIXME: Iterative?
BSTree *_bst_insert_internal(BSTree *root, void *val, size_t element_size) {
	if(!val) return NULL;
	if(!root) return bst_create(val, element_size);
    if(memcmp(root->val, val, root->size_element) < 0)
        root->right = _bst_insert_internal(root->right, val, element_size);
    else
        root->left = _bst_insert_internal(root->left, val, element_size);

	_bst_update_height(root);

	return _bst_rebalance(root);
}

bool bst_insert(BSTree **root, void *val) {
	if(!root || !*root || !val) return false;

	*root = _bst_insert_internal(*root, val, (*root)->size_element);

    return true;
}

//FIXME: iterative?
BSTree *_bst_remove_internal(BSTree *root, void *val) {
    if(!root || !val) return NULL;
	int res = memcmp(root->val, val, root->size_element);
    if(res == 0) {
        if(root->left || root->right) {
        	if(root->left && root->right) {
				BSTree *aux = root->left;
				while(aux->right)
					aux = aux->right;
				free(root->val);
				root->val = aux->val;
				aux->val = calloc(1, aux->size_element);
				if(!(aux->val)) return root;
				memmove(aux->val, val, aux->size_element);
				root->left = _bst_remove_internal(root->left, val);
				return root;
			}
			BSTree *aux = root->left ? root->left : root->right;
			root->left = NULL;
			root->right = NULL;
			bst_delete(&root);
			return aux;
        }
		root->left = NULL;
		root->right = NULL;
		bst_delete(&root);
        return NULL;
    }
    if(res > 0)
        root->left = _bst_remove_internal(root->left, val);
    if(res < 0)
        root->right = _bst_remove_internal(root->right, val);
	
	root->height =_bst_max_impl(bst_height(root->left), bst_height(root->right)) + 1;
	return _bst_rebalance(root);
}

bool bst_remove(BSTree **root, void *val) {
    if(!*root) return false;
	*root = _bst_remove_internal(*root, val);
	return true;
}

BSTree *bst_search(BSTree *root, void *val){
    if (!root || !val) return NULL;
    int res = memcmp(root->val, val, root->size_element);
	if(res == 0)
        return root;
    if(res > 0) {
        root = root->left;
        return bst_search(root, val);
    }
    else {
        root = root->right;
        return bst_search(root, val);
    }
    return NULL;
}

// BSTree *bst_invert_tree(BSTree *root) {
//     if (!root) return 0;
//
//     BSTree *helper;
//     helper = root->left;
//     root->left = root->right;
//     root->right = helper;
//
//     bst_invert_tree(root->left);
//     bst_invert_tree(root->right);
//
//     return root;
// }

#ifdef __DEBUG__
#include <math.h> //should also compile with -lm
int _bst_display_tree(char ** buffer, BSTree * no, int level, double h_position, int cols){
	char * ptr;
	int i, col, a, b;
	double offset;
	
	if(!no) return level;
	col = (int)(h_position * cols);
	offset = 1.0 / pow(2, level + 2);

	ptr = buffer[1 + level * 3] + col;
	sprintf(ptr, "%03d", *(int*)no->val);
	*(ptr + strlen(ptr)) = ' ';

	if(no->left || no->right)
		*(buffer[2 + level * 3] + col + 1) = '|';

	if(no->left){
		i = (int)((h_position - offset) * cols);
		*(buffer[3 + level * 3] + 1 + i) = '|';
		i++;
		for(; i <= col; i++)
			*(buffer[3 + level * 3] + 1 + i) = '-';
	}
	
	if(no->right){
		for(i = col; i < (int)((h_position + offset) * cols); i++)
			*(buffer[3 + level * 3] + 1 + i) = '-';
		*(buffer[3 + level * 3] + 1 + i) = '|';
	}

	a = _bst_display_tree(buffer, no->left, level + 1, h_position - offset, cols);
	b = _bst_display_tree(buffer, no->right, level + 1, h_position + offset, cols);

	if(a > b)
		return a;
	return b;
}

void bst_print(BSTree * no, int rows, int cols){
	int i, j, r;
	char ** buffer = (char **) malloc(rows * sizeof(char *));
	for(i = 0; i < rows; i++) {
		buffer[i] = (char *) malloc((cols + 1) * sizeof(char));
		for(j = 0; j < cols; j++)
			buffer[i][j] = ' ';
		buffer[i][j] = '\0';
	}
	r = _bst_display_tree(buffer, no, 0, 0.5, cols);
	for(i = 0; i < 3 * r; i++)
		printf("%s\n", buffer[i]);
}
#endif //__DEBUG__

void bst_delete(BSTree **root) {
	if(!root || !(*root)) return;
	bst_delete(&((*root)->left));
	bst_delete(&((*root)->right));
	free((*root)->val);
	free(*root);
	*root = NULL;
}


int main(void) {
	int a = 1337;
	BSTree *root = bst_create(&a, sizeof(int));
	bst_insert_const(root, 1, int);
	bst_insert_const(root, 2, int);
	bst_insert_const(root, 3, int);
	bst_insert_const(root, 4, int);
	bst_insert_const(root, 5, int);
	bst_insert_const(root, 6, int);
	bst_insert_const(root, 7, int);
	bst_insert_const(root, 8, int);
	bst_insert_const(root, 9, int);
	bst_insert_const(root, 10, int);

	bst_print(root, 300, 80);

	bst_remove_const(root, 10, int);
	a = 3;
	bst_remove_const(root, 3, int);
	a = 5;
	bst_remove_const(root, 5, int);
	bst_remove_const(root, 7, int);
	bst_print(root, 300, 80);
	return 0;
}
