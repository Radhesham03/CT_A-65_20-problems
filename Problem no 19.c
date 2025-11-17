#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int disc[MAX], low[MAX], parent[MAX];
int timeD;
int n;
int articulationFound = 0;

void DFS(int u) {
    visited[u] = 1;
    disc[u] = low[u] = ++timeD;
    int children = 0;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {

            if (!visited[v]) {
                children++;
                parent[v] = u;

                DFS(v);

                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                if (parent[u] == -1 && children > 1)
                    articulationFound = 1;

                if (parent[u] != -1 && low[v] >= disc[u])
                    articulationFound = 1;
            }

            
            else if (v != parent[u]) {
                if (low[u] > disc[v])
                    low[u] = disc[v];
            }
        }
    }
}

int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

   
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; 
    }

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    timeD = 0;

    DFS(0);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Graph is NOT Biconnected (Graph not connected)\n");
            return 0;
        }
    }

    if (articulationFound)
        printf("Graph is NOT Biconnected (Articulation point exists)\n");
    else
        printf("Graph IS Biconnected\n");

    return 0;
}
