#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define V 9

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int n) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist, V);
}

bool isValidGraph(int graph[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] < 0) {
                printf("Error: Negative weight detected at (%d, %d)\n", i, j);
                return false;
            }
        }
    }
    return true;
}

int main() {
    int graph[V][V];

    while (true) {
        printf("Enter a matrix (%dx%d):\n", V, V);
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                scanf("%d", &graph[i][j]);
                if (graph[i][j] < 0) {
                printf("Error: Negative weight detected at (%d, %d)\n", i, j);
                return false;
            }
            }
        }

        dijkstra(graph, 0);

        char Continue;
        printf("Do you want to enter another graph? (y/n): "); // so i can check for several inputs easialy
        scanf(" %c", &Continue);
        if (Continue != 'y' && Continue != 'Y') {
            break;
        }
    }

    return 0;
}
