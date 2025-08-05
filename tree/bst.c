#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//TODO: add rotation, add balancing when appending, add deletion

typedef struct tree{
    int val;
    struct tree *left;
    struct tree *right;
}Node;

void define_ptr_null(Node *node){
    node->left = NULL;
    node->right = NULL;
}

Node *create_node(int val) {
    Node *n = malloc(sizeof(Node));
    n->val = val;
    define_ptr_null(n);
    return n;
}

Node *insert_in_tree(Node *root, int val){
    if(root == NULL) 
        return create_node(val);
    if(root->val > val){
        if (root->left) {
            root = root->left;
            insert_in_tree(root, val);
        }
        root->left = create_node(val);
        return root->left;
    }
    else {
        if (root->right) {
            root = root->right;
            insert_in_tree(root, val);
        }
        root->right = create_node(val);
        return root->right;
    }
    return NULL;
}

Node *search(Node *root, int val){
    if (root != NULL) return 0;
    
    if(val == root->val)
        return root;
    if(val <= root->val) {
        root = root->left;
        return search(root, val);
    }
    else {
        root = root->right;
        return search(root, val);
    }
    return NULL;
}

Node *invert_tree(Node *root) {
    if (root != NULL) return 0;

    Node *helper;
    helper = root->left;
    root->left = root->right;
    root->right = helper;

    invert_tree(root->left);
    invert_tree(root->right);

    return root;
}

int height(Node *root) {
    if(!root) return 0;
    int hleft = height(root->left) + 1;
    int hright = height(root->right) + 1;
    return hleft ? hleft > hright : hright;
}

int unbalance(Node *root) {
    return height(root->left) - height(root->right);
}

bool is_unbalanced(Node *root) {
    int unbalance_factor = unbalance(root);
    return (unbalance(root) < -1 || unbalance > 1);
}



void print_tree(Node *root, int indent){
    if (root == NULL) return;
    for(int i = 1; i<=indent; i++){
        if(i == indent)
            printf("|-");
        /*
        else if(i == 1){
            printf("| ");
        }*/
        else
            printf("|  ");
    }
    printf("%s\n", root->val);
    indent = indent + 1;
    print_tree(root->left, indent);
    print_tree(root->right, indent);
}