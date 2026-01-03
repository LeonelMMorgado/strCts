#include "definition.h"

#define weighted true //add ifdef for weights??
#define directed true //add ifdef for directed??

typedef struct graph_matrix {
    int adj[V][V]; //only this one should exist in a struct (should it be a list of lists?
    int flag[V];
    int via[V];
    int dist[V];
    bool p[V];
} graph_matrix;

typedef struct node {
    int adj; //what node is adjacent (used in lists, so what node is adjacent to that in the list)
    int weight; //for unweighted graphs, you could just always use 1 for this.
    struct node * next;
} node;

typedef struct graph_list {
    int num;
    int flag;
    int via;
    int dist;
    node * start;   
} vertex;

graph_matrix * create_matrix();
bool create_edge_matrix(graph_matrix * g, int i, int j, int weight);
bool remove_edge_matrix(graph_matrix * g, int i, int j);
bool update_edge_matrix(graph_matrix * g, int i, int j, int new_weight);
bool create_edge_matrix_undirected(graph_matrix * g, int i, int j, int weight);
bool free_matrix(graph_matrix * g);
bool zero_flags_matrix(graph_matrix * g);
void print_matrix(graph_matrix * g);

vertex * create_graph_list();
node * create_node(int j, int weight);
node * search_edge(vertex * g, int i, int j);
node * search_deleting_edge(vertex * g, int i, int j, node ** prev);
bool insert_edge(vertex * g, int i, int j, int weight);
bool insert_edge_undirected(vertex * g, int i, int j, int weight);
bool insert_edge_searchless(vertex * g, int i, int j, int weight);
bool free_graph(vertex * g);
bool zero_flags_list(vertex * g);
void print_list(vertex * g);
