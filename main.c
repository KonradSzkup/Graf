#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"


int main() {
    int numVertices;
    char choice;
    Graph graph;

    printf("Podaj liczbe wierzcholkow: ");
    scanf("%d", &numVertices);

    if (numVertices > MAX_VERTICES || numVertices <= 0) {
        printf("Nieprawidlowa liczba wierzcholkow!\n");
        return 1;
    }

    initializeGraph(&graph, numVertices);

    printf("Czy graf ma byc losowy? (t/n): ");
    scanf(" %c", &choice);
    getchar(); // Oczyszczenie bufora wejściowego
    
    if (choice == 't' || choice == 'T') {
        generateRandomGraph(&graph);
    } else {
        int src, dest;
        printf("Podaj krawedzie w formacie (zrodlo cel), zakoncz -1 -1: \n");
        while (1) {
            scanf("%d %d", &src, &dest);
            if (src == -1 && dest == -1) break;
            if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
                addEdge(&graph, src, dest);
            } else {
                printf("Nieprawidlowa krawedz!\n");
            }
        }
    }
    
    printf("\nWygenerowany graf:\n");
    printGraph(&graph);
    return 0;
}
