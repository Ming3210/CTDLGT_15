#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int num;
    Node** adjLists;
    int* visited;      
    int* recursionStack;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));
    graph->recursionStack = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->recursionStack[i] = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

int detectDFS(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    graph->recursionStack[vertex] = 1;

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;

        if (graph->visited[adjVertex] == 0 && detectDFS(graph, adjVertex)) {
            return 1;
        }
        else if (graph->recursionStack[adjVertex]) {
            return 1;
        }

        temp = temp->next;
    }

    graph->recursionStack[vertex] = 0;
    return 0;
}

int hasCycle(Graph* graph) {
    for (int i = 0; i < graph->num; i++) {
        if (graph->visited[i] == 0) { 
            if (detectDFS(graph, i)) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int vertices, edges;
    printf("Nhap so dinh: ");
    scanf("%d", &vertices);
    printf("Nhap so canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Nhap cac canh (u, v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (hasCycle(graph)) {
        printf("Do thi co chu trinh\n");
    } else {
        printf("Do thi khong co chu trinh\n");
    }

    return 0;
}