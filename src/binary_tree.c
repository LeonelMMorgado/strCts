#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <binary_tree.h>

int64_t _bt_max_impl(int64_t a, int64_t b) {
	return a > b ? a : b;
}

int bt_common_int_compare(const void *val1, const void *val2, size_t element_size) {
	int v1 = *(int*)val1;
	int v2 = *(int*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_uint_compare(const void *val1, const void *val2, size_t element_size) {
	uint32_t v1 = *(uint32_t*)val1;
	uint32_t v2 = *(uint32_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_i64_compare(const void *val1, const void *val2, size_t element_size) {
	int64_t v1 = *(int64_t*)val1;
	int64_t v2 = *(int64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_u64_compare(const void *val1, const void *val2, size_t element_size) {
	uint64_t v1 = *(uint64_t*)val1;
	uint64_t v2 = *(uint64_t*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_float_compare(const void *val1, const void *val2, size_t element_size) {
	float v1 = *(float*)val1;
	float v2 = *(float*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_double_compare(const void *val1, const void *val2, size_t element_size) {
	double v1 = *(double*)val1;
	double v2 = *(double*)val2;
	return (v1 > v2) - (v1 < v2);
}

int bt_common_string_compare(const void *val1, const void *val2, size_t element_size) {
	char *s1 = *(char**)val1;
	char *s2 = *(char**)val2;
	return strcmp(s1, s2);
}

BinaryTreeNode *bt_create_node(void *val, size_t element_size) {
    BinaryTreeNode *n = malloc(sizeof(*n));
	if(!n)
		return NULL;
    n->val = malloc(element_size);
	if(!(n->val)) {
		free(n);
		return NULL;
	}
    memcpy(n->val, val, element_size);
	n->left = NULL;
	n->right = NULL;
	n->height = 0;
	return n;
}

BinaryTree *bt_create(size_t element_size, cmp_function compare_function) {
	BinaryTree *bst = malloc(sizeof(*bst));
	if(!bst) return NULL;
	bst->root = NULL;
	bst->size_element = element_size;
	if(compare_function)
		bst->compare_function = compare_function;
	else
		bst->compare_function = &memcmp;
	return bst;
}

int64_t bt_height(BinaryTreeNode *root) {
	if(!root) return -1;
	return root->height;
}

void bt_update_height(BinaryTreeNode *root) {
	root->height =_bt_max_impl(bt_height(root->left), bt_height(root->right)) + 1;
}

int64_t bt_balance(BinaryTreeNode *root) {
	if(!root) return 0;
	return bt_height(root->left) - bt_height(root->right);
}

bool bt_is_balanced(BinaryTreeNode *root) {
	int64_t balance_factor = bt_balance(root);
	return !(balance_factor < -1 || balance_factor > 1);
}

BinaryTreeNode *_bt_rotate_left(BinaryTreeNode*root) {
	if(!root) return NULL;
	if(!(root->right)) return NULL;
	BinaryTreeNode *right = root->right;
	BinaryTreeNode *rl = right->left;

	right->left = root;
	root->right = rl;

	bt_update_height(root);
	bt_update_height(right);

	return right;
}

BinaryTreeNode *_bt_rotate_right(BinaryTreeNode*root) {
	if(!root) return NULL;
	if(!(root->left)) return NULL;
	BinaryTreeNode *left = root->left;
	BinaryTreeNode *lr = left->right;

	left->right = root;
	root->left = lr;

	bt_update_height(root);
	bt_update_height(left);

	return left;
}

BinaryTreeNode *_bt_rebalance(BinaryTreeNode*root) {
	int64_t factor = bt_balance(root);

	if(factor > 1) {
		if(bt_balance(root->left) < 0)
			root->left = _bt_rotate_left(root->left);
		return _bt_rotate_right(root);
	}
	if(factor < -1) {
		if(bt_balance(root->right) > 0)
			root->right = _bt_rotate_right(root->right);
    	return _bt_rotate_left(root);
	}

	return root;
}

BinaryTreeNode *_bt_insert_internal(BinaryTree *root, BinaryTreeNode *node, void *val) {
	if(!root || !val) return NULL;
	if(!node) return bt_create_node(val, root->size_element);
    int res = root->compare_function(node->val, val, root->size_element);
	if(res < 0) {
		BinaryTreeNode *temp = _bt_insert_internal(root, node->right, val);
		if(temp) node->right = temp;
	}
    else if(res > 0) {
		BinaryTreeNode *temp = _bt_insert_internal(root, node->left, val);
		if(temp) node->left = temp;
	}
	else
		return node;

	bt_update_height(node);
	return _bt_rebalance(node);
}

bool bt_insert(BinaryTree *root, void *val) {
	if(!root || !val) return false;

	root->root = _bt_insert_internal(root, root->root, val);

    return true;
}

BinaryTreeNode *_bt_remove_internal(BinaryTree *root, BinaryTreeNode *node, void *val) {
    if(!root || !node || !val) return NULL;
	int res = root->compare_function(node->val, val, root->size_element);
    if(res == 0) {
        if(!(node->left) || !(node->right)) {
			BinaryTreeNode *aux = node->left ? node->left : node->right;
			if(aux) {
				BinaryTreeNode *to_free = node;
				node = aux;
				to_free->left = NULL;
				to_free->right = NULL;
				bt_delete_node(to_free);
				return node;
			}
			aux = node;
			node = NULL;
			bt_delete_node(aux);
        }
		else {
			BinaryTreeNode *aux = node->left;
			while(aux->right)
				aux = aux->right;
			void *temp = node->val;
			node->val = aux->val;
			aux->val = temp;
			node->left = _bt_remove_internal(root, node->left, aux->val);
		}
    }
	else if(res > 0)
        node->left = _bt_remove_internal(root, node->left, val);
	else if(res < 0)
        node->right = _bt_remove_internal(root, node->right, val);

	if(!node) return NULL;
	
	bt_update_height(node);
	return _bt_rebalance(node);
}

bool bt_remove(BinaryTree *root, void *val) {
    if(!root|| !(root->root) || !val) return false;
	root->root = _bt_remove_internal(root, root->root, val);
	return true;
}

BinaryTreeNode *_bt_search_internal(BinaryTree *root, BinaryTreeNode *node, void *val) {
	if(!root || !node || !val) return NULL;
    int res = root->compare_function(node->val, val, root->size_element);
	if(res == 0)
        return node;
    if(res > 0) {
        node = node->left;
        return _bt_search_internal(root, node, val);
    }
    else {
        node = node->right;
        return _bt_search_internal(root, node, val);
    }
    return NULL;
}

BinaryTreeNode *bt_search(BinaryTree *root, void *val){
    if (!root || !val) return NULL;
	
	return _bt_search_internal(root, root->root, val);
}

// BinaryTreeNode *bt_invert_tree(BinaryTreeNode *root) {
//     if (!root) return 0;
//
//     BinaryTreeNode *helper;
//     helper = root->left;
//     root->left = root->right;
//     root->right = helper;
//
//     bt_invert_tree(root->left);
//     bt_invert_tree(root->right);
//
//     return root;
// }

#ifdef __DEBUG__
#include <math.h> //should also compile with -lm
int _bt_display_tree(char ** buffer, BinaryTreeNode *no, int level, double h_position, int cols){
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

	a = _bt_display_tree(buffer, no->left, level + 1, h_position - offset, cols);
	b = _bt_display_tree(buffer, no->right, level + 1, h_position + offset, cols);

	if(a > b)
		return a;
	return b;
}

void _bt_print_internal(BinaryTreeNode *no, int rows, int cols){
	int i, j, r;
	char ** buffer = (char **) malloc(rows * sizeof(char *));
	for(i = 0; i < rows; i++) {
		buffer[i] = (char *) malloc((cols + 1) * sizeof(char));
		for(j = 0; j < cols; j++)
			buffer[i][j] = ' ';
		buffer[i][j] = '\0';
	}
	r = _bt_display_tree(buffer, no, 0, 0.5, cols);
	for(i = 0; i < 3 * r; i++)
		printf("%s\n", buffer[i]);
}

void bt_print(BinaryTree *root, int rows, int cols) {
	_bt_print_internal(root->root, rows, cols);
}
#endif //__DEBUG__

void bt_delete_node(BinaryTreeNode *node) {
	if(!node) return;
	bt_delete_node(node->left);
	bt_delete_node(node->right);
	free(node);
}

void bt_delete(BinaryTree **root) {
	if(!root || !(*root)) return;
	bt_delete_node((*root)->root);
	free(*root);
	*root = NULL;
}

