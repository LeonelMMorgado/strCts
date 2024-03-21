#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char nome[32];
    struct Node* child;
    struct Node* sibling;
} Node;

Node* criarNo(char* nome) {
    Node* no = (Node*)malloc(sizeof(Node));
    strcpy(no->nome, nome);
    no->child = NULL;
    no->sibling = NULL;
    return no;
}

void adicionar_child(Node* pai, Node* child) {
    if(pai->child == NULL) {
        pai->child = child;
    } else {
        Node* sibling = pai->child;
        while(sibling->sibling != NULL) {
            sibling = sibling->sibling;
        }
        sibling->sibling = child;
    }
}

void imprimirArvore(Node* raiz, int nivel) {
    for(int i = 0; i < nivel; i++) {
        if(i==nivel-1){
            printf("|-");
        }
        else {
            printf("|  ");
        }
    }
    printf("%s\n", raiz->nome);
    Node* child = raiz->child;
    while(child != NULL) {
        imprimirArvore(child, nivel + 1);
        child = child->sibling;
    }
}