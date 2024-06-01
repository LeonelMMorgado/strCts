#include "queue_stack.h"

//
queue * create_queue() {
    queue * q = (queue *)malloc(sizeof(queue));
    q->rear = -1;
    q->front = -1;
    return q;
}

bool is_queue_full(queue * q) {
    return q->rear == V - 1 ? true : false;
}

bool enqueue(queue * q, long i) {
    if (q == NULL) return false;
    if (is_queue_full(q)) return false;
    q->rear = q->rear + 1;
    q->data[q->rear] = i;
    q->front = true;
    return true;
}

long dequeue(queue * q) {
    if (q == NULL) return (long)false;
    if (q->rear == -1) return (long)false;
    long data = q->data[0];
    for(long i = 0; i < q->rear; i++) {
        q->data[i] = q->data[i + 1];
    }
    q->rear = q->rear - 1;
    //q->rear + 1 ? q->front = true : q->front = false; this doesn't work i dunno why
    if (q->rear + 1) {
        q->front = true;
    }
    else {
        q->front = false;
    }
    return data;
}

bool free_queue(queue * q) {
    if(q == NULL) return false;
    free(q->data);
    free(q);
    return true;
}
//

//
stack * create_stack() {
    stack * s = (stack *)malloc(sizeof(stack));
    s->rear = -1;
    return s;
}

bool is_stack_full(stack * s) {
    return s->rear == V - 1 ? true : false;
}

bool push(stack * s, long i) {
    if (s == NULL) return false;
    if (is_stack_full(s)) return false;
    s->rear = s->rear + 1;
    s->data[s->rear] = i;
    return true;
}

long pop(stack * s) {
    if (s == NULL) return (long)false;
    if (s->rear == -1) return (long)false;
    s->rear = s->rear - 1;
    return s->data[s->rear + 1];
}

bool free_stack(stack * s) {
    if(s == NULL) return false;
    free(s->data);
    free(s);
    return true;
}
//