#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//TODO: add rotation, add balancing when appending, add deletion

typedef struct _node{
    void *val;
    size_t size_element;
    struct _node *left;
    struct _node *right;
}Node;

void define_ptr_null(Node *node){
    node->left = NULL;
    node->right = NULL;
}

Node *create_node(void *val, size_t element_size) {
    Node *n = malloc(sizeof(Node));
    n->size_element = element_size;
    n->val = malloc(element_size);
    memmove(n->val, val, element_size);
    define_ptr_null(n);
    return n;
}

Node *insert_in_tree(Node *root, void *val, size_t element_size) {
    if(!root)
        return create_node(val, element_size);
    Node *inserted = NULL;
    if(memcmp(root->val, val, element_size) > 0)
        inserted = insert_in_tree(root->left, val, element_size);
    else
        inserted = insert_in_tree(root->right, val, element_size);
    if(is_unbalanced(root)) avl_balance(root);
    return inserted;
}

void remove_from_tree(Node *root, void *val, size_t element_size) {
    if(!root) return;
    if(memcmp(root->val, val, element_size) == 0) {
        if(root->left || root->right) {

        }
        free(root->val);
        free(root);
        return;
    }
    if(memcmp(root->val, val, element_size) > 0) {
        if(memcmp(root->left->val, val, element_size) == 0) {
            //achou
        }
        remove_from_tree(root->left, val, element_size);
        return;
    }
    if(memcmp(root->val, val element_size) < 0) {
        if(memcmp(root->right->val, val, element_size) == 0) {
            //achou
        }
        remove_from_tree(root->right, val, element_size);
    }
}

void free_tree(Node *root) {
    if(!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

Node *search(Node *root, void *val, size_t element_size){
    if (!root) return NULL;
    if(root->size_element != element_size) return NULL;
    if(memcmp(root->val, val, element_size) == 0)
        return root;
    if(val <= root->val) {
        root = root->left;
        return search(root, val, element_size);
    }
    else {
        root = root->right;
        return search(root, val, element_size);
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
    return hleft > hright ? hleft : hright;
}

int unbalance(Node *root) {
    return height(root->right) - height(root->left);
}

bool is_unbalanced(Node *root) {
    int balance_factor = unbalance(root);
    return (balance_factor < -1 || balance_factor > 1);
}

bool avl_balance(Node *root) {
    return false;
}

// void print_tree(Node *root, int indent){
//     if (root == NULL) return;
//     for(int i = 1; i<=indent; i++){
//         if(i == indent)
//             printf("|-");
//         /*
//         else if(i == 1){
//             printf("| ");
//         }*/
//         else
//             printf("|  ");
//     }
//     printf("%s\n", root->val);
//     indent = indent + 1;
//     print_tree(root->left, indent);
//     print_tree(root->right, indent);
// }
