#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {	
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void BFS(Graph* graph, int start, int target) {
    int* prev = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        prev[i] = -1;
    }

    int queue[graph->numVertices];
    int front = 0, rear = 0;

    graph->visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int currentVertex = queue[front++];
        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                prev[adjVertex] = currentVertex;
                queue[rear++] = adjVertex;

                if (adjVertex == target) {
                    front = rear; 
                    break;
                }
            }
            temp = temp->next;
        }
    }

    if (prev[target] != -1) {
        printf("Duong di ngan nhat tu %d den %d la: ", start, target);
        int path[graph->numVertices];
        int count = 0;
        for (int at = target; at != -1; at = prev[at]) {
            path[count++] = at;
        }
        for (int i = count - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("Khong co duong di tu %d den %d.\n", start, target);
    }

    free(prev);
}

int main() {
    int ver, edges;
    printf("Nhap so dinh: ");
    scanf("%d", &ver);
    printf("Nhap so canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(ver);

    printf("Nhap cac canh (u, v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int start, target;
    printf("Nhap dinh bat dau: ");
    scanf("%d", &start);
    printf("Nhap dinh dich: ");
    scanf("%d", &target);

    BFS(graph, start, target);

    return 0;
}