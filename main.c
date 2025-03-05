#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include <locale.h>


int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    int numVertices, choice, src, dest, weight;
    Graph graph;
    
    printf("Podaj liczbę wierzchołków: ");
    scanf("%d", &numVertices);
    if (numVertices > MAX_VERTICES || numVertices <= 0) {
        printf("Nieprawidłowa liczba wierzchołków!\n");
        return 1;
    }
    initializeGraph(&graph, numVertices);
    
    while (1) {
        printf("\nMENU:\n");
        printf("1. Wygeneruj losowy graf\n");
        printf("2. Dodaj krawędź\n");
        printf("3. Usuń krawędź\n");
        printf("4. Wyświetl graf\n");
        printf("5. Zapisz graf do pliku\n");
        printf("6. Wczytaj graf z pliku\n");
        printf("7. Wyjście\n");
        printf("Wybór: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                generateRandomGraph(&graph);
                break;
            case 2:
                printf("Podaj krawędź (źródło, cel, waga): ");
                scanf("%d %d %d", &src, &dest, &weight);
                addEdge(&graph, src, dest, weight);
                break;
            case 3:
                printf("Podaj krawędź do usunięcia (źródło, cel): ");
                scanf("%d %d", &src, &dest);
                removeEdge(&graph, src, dest);
                break;
            case 4:
                printGraph(&graph);
                break;
            case 5:
                saveGraphToFile(&graph, "graf.txt");
                break;
            case 6:
                loadGraphFromFile(&graph, "graf.txt");
                break;
            case 7:
                return 0;
            default:
                printf("Nieprawidłowy wybór!\n");
        }
    }
    return 0;
}