#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <abstract_tree.h>

AbstractTree *at_create(void *val, size_t size) {
    AbstractTree* node = malloc(sizeof(*node));
    if(!node) return NULL;
    node->val = val;
    node->size = size;
    node->child = NULL;
    node->sibling = NULL;
    return node;
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
    printf("%p\n", root->val); //add way to print accordingly
    AbstractTree* child = root->child;
    while(child != NULL) {
        _at_print_tree_rec(child, level + 1);
        child = child->sibling;
    }
}

void at_print_tree(AbstractTree *root) {
    _at_print_tree_rec(root, 0);
}
