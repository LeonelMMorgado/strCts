#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <abstracttree.h>

AbstractTree *at_create(void *val, size_t size_elements) {
	return at_create_full(val, size_elements, NULL, NULL);
}

AbstractTree *at_create_full(void *val, size_t size_elements, compare_fn compare_function, destroy_fn destroy_function) {
    AbstractTree* node = malloc(sizeof(*node));
    if(!node) return NULL;
	node->element = malloc(size_elements);
	if(!node->element) {
		free(node);
		return NULL;
	}
	memcpy(node->element, val, size_elements);
    node->size_elements = size_elements;
    node->child = NULL;
    node->sibling = NULL;
	node->compare_function = compare_function;
	node->destroy_function = destroy_function;
    return node;
}

void at_change_comparator(AbstractTree *tree, compare_fn compare_function) {
	if(!tree) return;
	tree->compare_function = compare_function;
	if(!compare_function) tree->compare_function = &memcmp;
}

void at_change_destroyer(AbstractTree *tree, destroy_fn destroy_function) {
	if(!tree) return;
	tree->destroy_function = destroy_function;
}

void at_add_child(AbstractTree* parent, AbstractTree* child) {
    if(parent->child == NULL) {
        parent->child = child;
    } else {
        AbstractTree* sibling = parent->child;
        while(sibling->sibling != NULL) 
            sibling = sibling->sibling;
        sibling->sibling = child;
    }
}

void _at_print_tree_rec(AbstractTree* root, int level) {
    for(int i = 0; i < level; i++) {
        if(i==level-1)
            printf("─");
        else 
            printf("└");
    }
    printf("%p\n", root->element); //TODO: add way to print accordingly
    AbstractTree* child = root->child;
    while(child != NULL) {
        _at_print_tree_rec(child, level + 1);
        child = child->sibling;
    }
}

void at_print_tree(AbstractTree *root) {
    _at_print_tree_rec(root, 0);
}

bool at_destroy(AbstractTree **root) {
	if(!*root) return false;
	at_destroy(&((*root)->child));
	at_destroy(&((*root)->sibling));
	if((*root)->destroy_function)
		(*root)->destroy_function((*root)->element);
	free((*root)->element);
	free(*root);
	*root = NULL;
	return true;
}

