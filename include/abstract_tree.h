#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _abstract_tree {
    void *val;
    size_t size;
    struct _abst_tree *child;
    struct _abst_tree *sibling;
} AbstractTree;

AbstractTree *at_create(void *val, size_t size);

void at_add_child(AbstractTree* parent, AbstractTree* child);

void at_print_tree(AbstractTree *root);

