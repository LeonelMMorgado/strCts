/*
example usage:
BinaryTree *root = bt_create(sizeof(int), &bt_common_int_compare);
srand(time(NULL));
for(int i = 0; i < 17; i++) {
	int rndn = rand() % 1000;
	bt_insert(root, &rndn);
}

bt_print(root, 300, 80);

bt_delete(&root);
*/
#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "memclass.h"

#define bt_insert_const(bst, val, type) \
	do {\
		type var = (val);\
		bt_insert((bst), &var);\
	} while(0)

#define bt_remove_const(bst, val, type) \
	do {\
		type var = (val);\
		bt_remove((bst), &var);\
	} while(0)

typedef struct _bstree_node {
	void *element;
	struct _bstree_node *left;
	struct _bstree_node *right;
	int64_t height;
} BinaryTreeNode;

typedef struct _binary_search_tree {
    size_t size_elements;
    BinaryTreeNode *root;
	compare_fn compare_function;
	destroy_fn destroy_function;
} BinaryTree;

BinaryTreeNode *bt_create_node(void *val, size_t size_elements);
BinaryTree     *bt_create(size_t size_elements);
BinaryTree     *bt_create_comparator(size_t size_elements, compare_fn compare_function);
BinaryTree     *bt_create_destroyer(size_t size_elements, destroy_fn destroy_function);
BinaryTree     *bt_create_full(size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void            bt_change_comparator(BinaryTree *tree, compare_fn compare_function);
void            bt_change_destroyer(BinaryTree *tree, destroy_fn destroy_function);

int64_t bt_height(BinaryTreeNode *root);
void    bt_update_height(BinaryTreeNode *root);
int64_t bt_balance(BinaryTreeNode *root);
bool    bt_is_balanced(BinaryTreeNode *root);

bool bt_insert(BinaryTree *tree, void *val);

bool bt_remove(BinaryTree *tree, void *val);

BinaryTreeNode *bt_search(BinaryTree *tree, void *val);

// BinaryTreeNode *bt_invert_tree(BinaryTreeNode *root);

void bt_print(BinaryTree *tree, int rows, int cols);

void bt_destroy_node(BinaryTreeNode *node, destroy_fn destroy_function);
void bt_destroy(BinaryTree **tree);

#endif

