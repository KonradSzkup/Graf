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


// Funkcja dodająca krawędź do grafu
void addEdge(Graph* graph, int src, int dest);

// Funkcja generująca losowy graf
void generateRandomGraph(Graph* graph);

// Funkcja wyświetlająca graf
void printGraph(Graph* graph);