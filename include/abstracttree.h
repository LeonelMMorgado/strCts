#ifndef _ABST_TREE_H
#define _ABST_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memclass.h"

typedef struct _abstract_tree {
	void *element;
	size_t size_elements;
	struct _abstract_tree *child;
	struct _abstract_tree *sibling;
	compare_fn compare_function;
	destroy_fn destroy_function;
} AbstractTree;

AbstractTree *at_create(void *val, size_t size_elements);
AbstractTree *at_create_full(void *val, size_t size_elements, compare_fn compare_function, destroy_fn destroy_function);
void          at_change_comparator(AbstractTree *tree, compare_fn compare_function);
void          at_change_destroyer(AbstractTree *tree, destroy_fn destroy_function);

void at_add_child(AbstractTree* parent, AbstractTree* child);

void at_print_tree(AbstractTree *tree);

bool at_destroy(AbstractTree **tree);

#endif

