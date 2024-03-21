#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
    int val;
    struct tree * left;
    struct tree * right;
}node;

void print_tree(node * root, int indent){
    if (root == NULL) return;
    for(int i = 1; i<=indent; i++){
        if(i == indent){
            printf("|-");
        }/*
        else if(i == 1){
            printf("| ");
        }*/
        else
        {
            printf("|  ");
        }
        
    }
    printf("%s\n", root->val);
    indent = indent + 1;
    print_tree(root->left, indent);
    print_tree(root->right, indent);
}

void define_ptr_null(node * node){
    node->left = NULL;
    node->right = NULL;
}

node * create_node(node * root, int val){
    if(root == NULL) {
        root = (node *)malloc(sizeof(node));
        root->val = val;
        define_ptr_null(root);
        return root;
    }
    if(root->val > val){
        if (root->left)
        {
            root = root->left;
            create_node(root, val);
        }
        root->left = (node *)malloc(sizeof(node));
        node * new_node = root->left;
        define_ptr_null(new_node);
        new_node->val = val;
        return new_node;
    }
    else {
        if (root->right)
        {
            root = root->right;
            create_node(root, val);
        }
        root->right = (node *)malloc(sizeof(node));
        node * new_node = root->right;
        define_ptr_null(new_node);
        new_node->val = val;
        return new_node;
    }
    return NULL;
}

node * search(node * root, int val){
    if (root != NULL) return 0;
    
    if(val == root->val){
        return root;
    }
    if(val <= root->val){
        root = root->left;
        return search(root, val);
    }
    else {
        root = root->right;
        return search(root, val);
    }
    return NULL;
}

node * invert_tree(node * root) {
    if (root != NULL) return 0;

    node * helper;
    helper = root->left;
    root->left = root->right;
    root->right = helper;

    invert_tree(root->left);
    invert_tree(root->right);

    return root;
}