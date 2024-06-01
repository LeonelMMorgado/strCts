#include "graphs.h"

graph_matrix * linked_to_matrix(vertex * g) {
    graph_matrix * m = create_matrix();
    for (int i = 0; i < V; i++) {
        if (!g[i].start) continue;
        node * p = g[i].start;
        while(p) {
            create_edge_matrix(m, i, p->adj, p->weight);
            p = p->next;
        }
    }
    return m;
}

vertex * matrix_to_linked(graph_matrix * g) {
    vertex * v = create_graph_list();
    for (int i = 0; i < V; i++) {
        v[i].num = i;
        v[i].start = NULL;
        for(int j = 0; j < V; j++) {
            if (g->adj[i][j] == 0) continue;
            v[i].start = insert_edge_searchless(g, i, j, g->adj[i][j]);
        }
    }
    return v;
}