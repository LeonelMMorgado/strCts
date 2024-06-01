#include "queue_stack.h"
#include "graphs.h"
#include <limits.h>

//Matrix Functions
graph_matrix * create_matrix() {
    graph_matrix * m = (graph_matrix *)malloc(sizeof(graph_matrix));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            m->adj[i][j] = 0;
            m->flag[i] = 0;
            m->via[i] = -1;
            m->dist[i] = INT_MAX;
        }
    }
    return m;
}

bool create_edge_matrix(graph_matrix * g, int i, int j, int weight) {
    if (g == NULL) return false;
    if (i > V || j > V) return false;
    if (i < 0 || j < 0) return false;
    if (g->adj[i][j]) return false;
    if (weight <= 0) return false;
    g->adj[i][j] = weight;
    return true;
}

bool remove_edge_matrix(graph_matrix * g, int i, int j) {
    if (g == NULL) return false;
    if (i > V || j > V) return false;
    if (i < 0 || j < 0) return false;
    if (g->adj[i][j] == 0) return false;
    g->adj[i][j] = 0;
    return true;
}

bool update_edge_matrix(graph_matrix * g, int i, int j, int new_weight) {
    if (g == NULL) return false;
    if (i > V || j > V) return false;
    if (i < 0 || j < 0) return false;
    if (new_weight <= 0) return false;
    g->adj[i][j] = new_weight;
    return true;
}

bool create_edge_matrix_undirected(graph_matrix * g, int i, int j, int weight) {
    if (g == NULL) return false;
    if (i > V || j > V) return false;
    if (i < 0 || j < 0) return false;
    if (g->adj[i][j]) return false;
    if (weight <= 0) return false;
    g->adj[i][j] = weight;
    g->adj[j][i] = weight;
    return true;
}

bool free_matrix(graph_matrix * g){
    if(g == NULL) return false;
    free(g->adj);
    free(g);
    return true;
}

bool zero_flags_matrix(graph_matrix * g) {
    if (g == NULL) return false;
    for(int i = 0; i < V; i++) {
        g->flag[i] = 0;
        g->via[i] = -1;
        g->dist[i] = INT_MAX;
    }
    return true;
}

void print_matrix(graph_matrix * g){
    for (int i = 0; i < V; i++) {
        //printf("%d -> ", i);
        for (int j = 0; j < V; j++) {
            if(g->adj[i][j] == 0) continue;
            //printf("%d (%d) -> ", j, g->adj[i][j]);
        }
        //printf("\n");
    }
}
//End of Matrix Functions

//Linked List Functions
vertex * create_graph_list() {
    vertex * v = (vertex *)malloc(sizeof(vertex)*V);
    for (int i = 0; i < V; i++) {
        v[i].num = i;
        v[i].flag = 0;
        v[i].via = -1;
        v[i].dist = INT_MAX;
        v[i].start = NULL;
    }
    return v;
}

node * create_node(int j, int weight) {
    if (j < 0 || j >= V) return NULL;
    if (weight <= 0) return NULL;
    node * n  = (node *) malloc(sizeof(node));
    n->adj = j;
    n->weight = weight;
    n->next = NULL;
    return n;
}

node * search_edge(vertex * g, int i, int j) {
    if (g == NULL) return NULL;
    if (i < 0 || i >= V) return NULL;
    if (j < 0 || j >= V) return NULL;
    node * p = g[i].start;
    while (p) {
        if (p->adj == j) return p;
        p = p->next;
    }
    return NULL;
}

/*search_edge for exclusion*/
node * search_deleting_edge(vertex * g, int i, int j, node ** prev) {
    if (g == NULL) return NULL;
    if (i < 0 || i >= V) return NULL;
    if (j < 0 || j >= V) return NULL;
    *prev = NULL;
    node * p = g[i].start;
    while(p) {
        if (p->adj == j) return p;
        *prev = p;
        p = p->next;
    }
    return NULL;
}

bool insert_edge(vertex * g, int i, int j, int weight) {
    if (g == NULL) return false;
    if (i < 0 || i >= V) return false;
    if (j < 0 || j >= V) return false;
    if (weight <= 0) return false;
    node * p = search_edge(g, i, j);
    if (p) return false;
    node * n = create_node(j, weight);
    node * helper = g[i].start;
    g[i].start = n;
    n->next = helper;
    return true;
}

bool inserted_edge_undirected(vertex * g, int i, int j, int weight) {
    if (g == NULL) return false;
    if (i < 0 || i >= V) return false;
    if (j < 0 || j >= V) return false;
    if (weight <= 0) return false;
    node * p = create_node(j, weight);
    node * helper = g[i].start;
    g[i].start = p;
    p->next = helper;
    p = create_node(i, weight);
    helper = g[j].start;
    g[j].start = p;
    return true;
}

bool insert_edge_searchless(vertex * g, int i, int j, int weight) {
    if (g == NULL) return false;
    if (i < 0 || i >= V) return false;
    if (j < 0 || j >= V) return false;
    if (weight <= 0) return false;
    node * n = create_node(j, weight);
    node * helper = g[i].start;
    g[i].start = n;
    n->next = helper;
    return true;
}

bool free_graph(vertex * g) {
    if(g == NULL) return false;
    stack * s = create_stack();
    for (int i = 0; i < V; i++) {
        node * p = g[i].start;
        while (p) {
            push(s, (int)p);
            p = p->next;
        }
        while(!is_stack_full(s)) {
            node * q = (node *)pop(s);
            free(q);
        }
    }
    free(g);
    return true;
}

bool delete_edge(vertex * g, int i, int j) {
    node * ant;
    node * p = search_deleting_edge(g, i, j, &ant);
    if (p == NULL) return false;
    if (ant) ant->next = p->next;
    else g[i].start = p->next;
    free(p);
    return true;
}

bool zero_flags_list (vertex * g) {
    if (g == NULL) return false;
    for (int i = 0; i < V; i++) {
        g[i].flag = 0;
        g[i].via = -1;
        g[i].dist = INT_MAX;
    }
    return true;
}

void print_list(vertex * g) {
    for (int i = 0; i < V; i++) {
        node * p = g[i].start;
        //printf("%d -> ", g[i].num);
        while(p) {
            //printf("%d (%d) -> ", p->adj, p->weight);
        }
        //printf("\n");
    }
}
//End of Graph Functions