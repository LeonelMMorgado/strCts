#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char lexeme[256];
    char token[256];
    char attribute[256];
    struct node * next;
}node;

typedef struct list{
    node * head;
    node * last_created;
}list;

list * create_list(){
    list * new_list = (list *)malloc(sizeof(list));
    new_list->head = NULL;
    new_list->last_created = NULL;
    return new_list;
}

node * search_node(list*curr_list, char*lexem){
    node * checker = curr_list->head;
    while(checker != NULL){
        if(strcmp(checker->lexeme, lexem)==0){
            return checker;
        }
        checker = checker->next;
    }
    return NULL;
}

node * new_node(list * curr_list, char*lexem, char*tok, char*attr){
    if(curr_list->last_created != NULL){
        node * refer = search_node(curr_list, lexem);
        if(refer == NULL){
            refer = curr_list->last_created;
            refer->next = (node *)malloc(sizeof(node));
            refer = refer->next;
            curr_list->last_created = refer;
            strcpy(refer->lexeme, lexem);
            strcpy(refer->token, tok);
            strcpy(refer->attribute, attr);
            refer->next = NULL;
            return refer;
        }
        else{
            printf("Lexeme %s already in list.\n", lexem); 
            return refer;
        }
    }
    else{
        curr_list->head = (node *)malloc(sizeof(node));
        curr_list->last_created = curr_list->head;
        node * refer = curr_list->last_created;
        strcpy(refer->lexeme, lexem);
        strcpy(refer->token, tok);
        strcpy(refer->attribute, attr);
        refer->next = NULL;
        return refer;
    }
}

void write_list(list*curr_list){
    node * writer = curr_list->head;
    printf("Tokens are in inputed order:\n");
    while(writer != NULL){
        printf("%s | %s | %s\n", writer->lexeme, writer->token, writer->attribute);
        writer=writer->next;
    }
    printf("-----------------------------\n");
}

void write_id_list(list*curr_list){
    node * writer = curr_list->head;
    printf("IDs are in inputed order:\n");
    while(writer != NULL){
        if(strcmp(writer->token, "ID") == 0){
            printf("%s\n", writer->lexeme);
        }
        writer = writer->next;
    }
}

int main(){
    list * my_list = create_list();
    int answ = 0;
    char lexe[256];
    char toke[256];
    char attribu[256];
    while(answ!=5){
        printf("What would you like to do?\n   1- Input new lexem (press 1);\n   2- Write list (press 2);\n   3- Write list of only IDs (press 3)\n   X- Exit (press 5);\n");
        scanf("%d", &answ);
        if(answ==1){
            printf("What is the lexeme you'd like to input?\n");
            scanf("%s", lexe);
            printf("What is its token?\n");
            scanf("%s", toke);
            printf("What is its attribute?\n");
            scanf("%s", attribu);
            new_node(my_list, lexe, toke, attribu);
        }
        else if(answ==2){
            write_list(my_list);
        }
        else if(answ==3){
            write_id_list(my_list);
        }
        else if(answ==5){
            printf("Bye bye!");
            break;
        }
        else{
            printf("Please input a valid answer...\n");
        }
    }

    return 0;
}