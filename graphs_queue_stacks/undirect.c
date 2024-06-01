#include "graphs.h"

graph_matrix * direct_matrix(graph_matrix * g) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->adj[j][i] = g->adj[i][j];
        }
    }
    return g;
}

vertex * direct_vertex(vertex * g) {
    for (int i = 0; i < V; i++) {
        node * p = g[i].start;
        while (p) {
            insert_edge_searchless(g, p->adj, i, p->weight);
            p = p->next;
        }
    }
    return g;
}