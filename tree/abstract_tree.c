#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char name[32];
    struct Node* child;
    struct Node* sibling;
} Node;

Node* create_node(char* name) {
    Node* node = malloc(sizeof(*node));
    strcpy(node->name, name);
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

void print_tree(Node* root, int level) {
    for(int i = 0; i < level; i++) {
        if(i==level-1)
            printf("|-");
        else 
            printf("|  ");
    }
    printf("%s\n", root->name);
    Node* child = root->child;
    while(child != NULL) {
        imprimirArvore(child, level + 1);
        child = child->sibling;
    }
}
