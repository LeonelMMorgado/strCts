#include "definition.h"

typedef struct queue {
    long data[V];
    int rear;
    bool front;
} queue;

typedef struct stack {
    long data[V];
    int rear;
} stack;

queue * create_queue();
bool is_queue_full(queue * q);
bool enqueue(queue * q, long i);
long dequeue(queue * q);
bool free_queue(queue * q);

stack * create_stack();
bool is_stack_full(stack * s);
bool push(stack * s, long i);
long pop(stack * s);
bool free_stack(stack * s);