#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node* adjList[MAX];
};

int visited[MAX];
int stack[MAX];
int top = -1;

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void topoDFS(struct Graph* graph, int v) {
    visited[v] = 1;

    struct Node* temp = graph->adjList[v];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            topoDFS(graph, temp->vertex);
        temp = temp->next;
    }

    stack[++top] = v;
}

void topologicalSort(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = 0;

    for (int i = 0; i < graph->numVertices; i++)
        if (!visited[i])
            topoDFS(graph, i);

    printf("\nTopological Order: ");
    while (top != -1)
        printf("%d ", stack[top--]);

    printf("\n");
}

int main() {
    int vertices, edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v) for directed graph:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    topologicalSort(graph);

    return 0;
}
