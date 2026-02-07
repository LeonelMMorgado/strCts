#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    void *val;
    size_t size;
    struct Node* child;
    struct Node* sibling;
} Node;

Node* create_node(void *val, size_t size) {
    Node* node = malloc(sizeof(*node));
    if(!node) return NULL;
    node->val = val;
    node->size = size;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

void add_child(Node* parent, Node* child) {
    if(parent->child == NULL) {
        parent->child = child;
    } else {
        Node* sibling = parent->child;
        while(sibling->sibling != NULL) 
            sibling = sibling->sibling;
        sibling->sibling = child;
    }
}

void _print_tree_rec(Node* root, int level) {
    for(int i = 0; i < level; i++) {
        if(i==level-1)
            printf("─");
        else 
            printf("└");
    }
    printf("%p\n", root->val); //add way to print accordingly
    Node* child = root->child;
    while(child != NULL) {
        _print_tree_rec(child, level + 1);
        child = child->sibling;
    }
}

void print_tree(Node *root) {
    _print_tree_rec(root, 0);
}
