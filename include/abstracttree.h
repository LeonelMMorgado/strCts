#ifndef _ABST_TREE_H
#define _ABST_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memclass.h"

typedef struct _abstract_tree {
	void *val;
	size_t size;
	struct _abstract_tree *child;
	struct _abstract_tree *sibling;
	compare_fn compare_function;
	destroy_fn destroy_function;
} AbstractTree;

AbstractTree *at_create(void *val, size_t size, compare_fn compare_function, destroy_fn destroy_function);

void at_add_child(AbstractTree* parent, AbstractTree* child);

void at_print_tree(AbstractTree *root);

bool at_destroy(AbstractTree **root);

#endif

