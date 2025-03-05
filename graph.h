#define MAX_VERTICES 100

// Struktura krawędzi
typedef struct Edge {
    int destination;
    int weight;
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
void addEdge(Graph* graph, int src, int dest, int weitght);

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