#include <stdio.h>
#include ".\graphs.h"
#include ".\queue_stack.h"

//algos viwed in DSA class

//DFS, BFS, Dijkstra and Floyd implemented with matrix
void DFS_M(graph_matrix * g, int i) {
    g->flag[i] = 1; //found
    //printf("visited %d", i);
    for (int j = 0; j < V; j++) {
        if (g->adj[i][j]) {
            if (g->flag[j] == 0) { //include dist and via changes;
                DFS_M(g, j);
            }
        }
    }
    g->flag[i] = 2;
}

void BFS_M(graph_matrix * g, int i, int j) {
    zero_flags_matrix(g);
    g->dist[i] = 0;
    queue * q =  create_queue();
    g->flag[i] = 1;
    enqueue(q, (long)i);
    while (q->front) {
        i = (int)dequeue(q);
        //printf("visited %d\n", i);
        g->flag[i] = 2;
        if (i == j) printf("found %d\n", j);
        for (int j = 0; j < V; j++) {
            if (g->adj[i][j] && g->flag[j] == 0) {
                g->flag[j] = 1;
                g->via[j] = i;
                g->dist[j] = g->dist[i] + g->adj[i][j];
                enqueue(q, (long)j);
            }
        }
    }
}

void dijkstra(graph_matrix * g, int i, int j) {
    for (int k = 0; k < V; k++) {
        g->p[k] = false;
        g->dist[k] = INT_MAX;
        g->via[k] = -1;
    }
    g->dist[i] = 0;
    g->p[i] = true;
    while(i != j){
        int next = -1;
        int best_dist = INT_MAX;
        for (int count = 0; count < V; count++) {
            if (g->adj[i][j] > 0) {
                int new_dist = g->dist[i] + g->adj[i][j];
                if (new_dist < g->dist[j]) {
                    g->dist[j] = new_dist;
                    g->via[j] = i;
                }
            }
            if (g->dist[j] < best_dist && g->p[j] == 0) {
                best_dist = g->dist[j];
                next = j;
            }
        }
        if (next == -1) return;
        g->p[i] = true;
        i = next;
    }
    return;
}
//


//DFS, BFS, Dijkstra and Floyd implemented with linked list
void DFS_L(vertex * g, int i) {
    g[i].flag = 1; //found
    node * p = g[i].start;
    //printf("visited %d", p->adj);
    while (p){
        if (g[p->adj].flag == 0) { //include dist and via changes;
            DFS_L(g, p->adj);
        }
        p = p->next;
    }
    g[i].flag = 2;
}

node * BFS_L(vertex * g, int i, int obj) {
    node * resp = NULL;
    queue * q = create_queue();
    zero_flags_list(g);
    enqueue(q, (long)i);
    g[i].flag = 1;
    while (q->front) {
        i = dequeue(q);
        g[i].flag = 2;
        if (g[i].num == obj) {
            node * new = (node *)malloc(sizeof(node));
            new->adj = i;
            new->next = resp;
            resp = new;
        }
        node * p = g[i].start;
        while (p) {
            if(g[p->adj].flag == 0) {
                enqueue(q, p->adj);
                g[p->adj].flag = 1;
                g[p->adj].via = i;
                g[p->adj].dist = g[i].dist + 1;
            }
            p = p->next;
        }
    }
    return resp;
}
//pode ter erro
