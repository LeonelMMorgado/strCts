#include "graphs.h"

graph_matrix * tranpose_matrix(graph_matrix * g, int N) {
    graph_matrix * m = (graph_matrix *)malloc(sizeof(graph_matrix));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m->adj[i][j] = g->adj[j][i];
        }
    }
    return m;
}

vertex * transpose_linked(vertex * g, int N) {
    vertex * v = create_graph_list();
    for (int i = 0; i < N; i++) {
        node * p = g[i].start;
        while(p) {
            insert_edge_searchless(v, p->adj, g[i].num, p->weight);
        }
    }
    return v;
}