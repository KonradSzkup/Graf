#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

#define MAX_VERTICES 100

// Funkcja inicjalizująca graf
void initializeGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        graph->vertices[i].id = i;
        graph->vertices[i].edges = NULL;
    }
}

// Funkcja dodająca krawędź do grafu
void addEdge(Graph* graph, int src, int dest) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->destination = dest;
    newEdge->next = graph->vertices[src].edges;
    graph->vertices[src].edges = newEdge;
}

// Funkcja generująca losowy graf
void generateRandomGraph(Graph* graph) {
    srand(time(NULL));
    for (int i = 0; i < graph->numVertices; i++) {
        int edges = rand() % (graph->numVertices - 1) + 1;
        for (int j = 0; j < edges; j++) {
            int dest = rand() % graph->numVertices;
            if (dest != i) {
                addEdge(graph, i, dest);
            }
        }
    }
}

// Funkcja wyświetlająca graf
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d -> ", i);
        Edge* current = graph->vertices[i].edges;
        while (current) {
            printf("%d ", current->destination);
            current = current->next;
        }
        printf("\n");
    }
}