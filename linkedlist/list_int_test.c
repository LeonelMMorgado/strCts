#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int value;
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

node * new_node(list * curr_list, int new_value){
    if(curr_list->last_created != NULL){
        node * refer = curr_list->last_created;
        refer->next = (node *)malloc(sizeof(node));
        refer = refer->next;
        curr_list->last_created = refer;
        refer->value = new_value;
        refer->next = NULL;
        return refer;
    }
    else{
        curr_list->head = (node *)malloc(sizeof(node));
        curr_list->last_created = curr_list->head;
        node * refer = curr_list->last_created;
        refer->value = new_value;
        refer->next = NULL;
        return refer;
    }
}


node * search_node(list*curr_list, int search_value){
    int ocurr = 0;
    node * checker = curr_list->head;
    while(checker != NULL){
        if(checker->value == search_value){
            ocurr = ocurr + 1;
        }
        checker = checker->next;
    }
    printf("found %d ocurrences of %d in the list.\n", ocurr, search_value);
    return NULL;
}

void write_list(list*curr_list){
    node * writer = curr_list->head;
    printf("Values are in inputed order:\n");
    while(writer != NULL){
        printf("%d\n", writer->value);
        writer=writer->next;
    }
    printf("-----------------------------\n");
}

int main(){
    list * my_list = create_list();
    int answ = 0;
    int value;
    while(answ!=5){
        printf("What would you like to do?\n   1- Input new value (press 1);\n   2- Search for value (press 2);\n   3- Write list of values (press 3);\n   X- Exit (press 5);\n");
        scanf("%d", &answ);
        if(answ==1){
            printf("What is the value you'd like to input?\n");
            scanf("%d", &value);
            new_node(my_list, value);
        }
        else if(answ==2){
            printf("Which one would you like to search from the list?\n");
            scanf("%d", &value);
            search_node(my_list, value);
        }
        else if(answ==3){
            write_list(my_list);
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