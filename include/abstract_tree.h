#ifndef _ABST_TREE_H
#define _ABST_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _abstract_tree {
	void *val;
	size_t size;
	struct _abstract_tree *child;
	struct _abstract_tree *sibling;
} AbstractTree;

AbstractTree *at_create(void *val, size_t size);

void at_add_child(AbstractTree* parent, AbstractTree* child);

void at_print_tree(AbstractTree *root);

#endif

