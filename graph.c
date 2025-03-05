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
void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->destination = dest;
    newEdge->weight = weight;
    newEdge->next = graph->vertices[src].edges;
    graph->vertices[src].edges = newEdge;
}

// Funkcja usuwająca krawędź
typedef struct Edge Edge;
void removeEdge(Graph* graph, int src, int dest) {
    Edge** current = &graph->vertices[src].edges;
    while (*current) {
        if ((*current)->destination == dest) {
            Edge* temp = *current;
            *current = (*current)->next;
            free(temp);
            printf("Usunięto krawędź %d -> %d\n", src, dest);
            return;
        }
        current = &(*current)->next;
    }
    printf("Krawędź %d -> %d nie istnieje.\n", src, dest);
}

// Funkcja generująca losowy graf
void generateRandomGraph(Graph* graph) {
    srand(time(NULL));
    for (int i = 0; i < graph->numVertices; i++) {
        int edges = rand() % (graph->numVertices - 1) + 1;
        for (int j = 0; j < edges; j++) {
            int dest = rand() % graph->numVertices;
            int weight = rand() % 10 + 1;
            if (dest != i) {
                addEdge(graph, i, dest, weight);
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
            printf("%d (waga: %d) ", current->destination, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

// Funkcja zapisu grafu do pliku
void saveGraphToFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Błąd zapisu do pliku!\n");
        return;
    }
    fprintf(file, "%d\n", graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++) {
        Edge* current = graph->vertices[i].edges;
        while (current) {
            fprintf(file, "%d %d %d\n", i, current->destination, current->weight);
            current = current->next;
        }
    }
    fclose(file);
    printf("Graf zapisany do pliku %s.\n", filename);
}

// Funkcja odczytu grafu z pliku
void loadGraphFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Błąd odczytu pliku!\n");
        return;
    }
    fscanf(file, "%d", &graph->numVertices);
    initializeGraph(graph, graph->numVertices);
    int src, dest, weight;
    while (fscanf(file, "%d %d %d", &src, &dest, &weight) == 3) {
        addEdge(graph, src, dest, weight);
    }
    fclose(file);
    printf("Graf wczytany z pliku %s.\n", filename);
}