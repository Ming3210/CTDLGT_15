#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int edges[MAX][MAX];
    int n; 
} Graph;

void initGraph(Graph *g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->edges[i][j] = 0;
        }
    }
}

void addEdge(Graph *g, int u, int v) {
    g->edges[u][v] = 1;
    g->edges[v][u] = 1; 
}

void DFS(Graph *g, int v, bool visited[]) {
    visited[v] = true;
    for (int i = 0; i < g->n; i++) {
        if (g->edges[v][i] && !visited[i]) {
            DFS(g, i, visited);
        }
    }
}

int countconnected(Graph *g) {
    bool visited[MAX] = {false};
    int count = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) {
            DFS(g, i, visited);
            count++;
        }
    }

    return count;
}

int main() {
    int V, E;
    printf("Nhap so dinh: ");
    scanf("%d", &V);
    printf("Nhap so canh: ");
    scanf("%d", &E);

    Graph g;
    initGraph(&g, V);

    printf("Nhap danh sach cac canh (u, v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    int connected = countconnected(&g);
    printf("So luong thanh phan lien thong: %d\n", connected);

    return 0;
}