#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100

// Struktura krawędzi
typedef struct Edge {
    int destination;
    struct Edge* next;
} Edge;

// Struktura wierzchołka
typedef struct Vertex {
    int id;
    Edge* edges;
} Vertex;

// Struktura grafu
typedef struct Graph {
    int numVertices;
    Vertex vertices[MAX_VERTICES];
} Graph;

// Funkcja inicjalizująca graf
void initializeGraph(Graph* graph, int numVertices);

// Funkcja sprawdzająca, czy krawędź już istnieje
int edgeExists(Graph* graph, int src, int dest);

// Funkcja dodająca krawędź do grafu
void addEdge(Graph* graph, int src, int dest);

// Funkcja usuwająca krawędź
typedef struct Edge Edge;
void removeEdge(Graph* graph, int src, int dest);

// Funkcja zapisu grafu do pliku
void saveGraphToFile(Graph* graph, const char* filename);

// Funkcja odczytu grafu z pliku
void loadGraphFromFile(Graph* graph, const char* filename);

// Funkcja generująca losowy graf
void generateRandomGraph(Graph* graph);

// Funkcja wyświetlająca graf
void printGraph(Graph* graph);

// Funkcja zapisu grafu do pliku DOT
void exportGraphToDOT(Graph* graph, const char* filename);

// Funkcja zwalniająca pamięć zajmowaną przez graf
void freeGraph(Graph* graph);

void generateGraph(const char* filename);

#endif