#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph.h"
#include "llm_graph.h"
#include <locale.h>


int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    int numVertices, choice, src, dest, weight;
    Graph graph;
    char mode;
    char nazwa_pliku[100];

    printf("Wybierz tryb:\n");
    printf("(M) Manualne tworzenie grafu\n");
    printf("(C) Tworzenie grafu z chatbotem\n");
    printf("Twój wybór: ");
    scanf(" %c", &mode);
    
    if (mode == 'C' || mode == 'c') {
        char input[256];
        printf("Podaj komendę dla chatbota (np. 'stwórz graf z 5 wierzchołkami'):\n");
        printf("Komenda: ");
        while (getchar() != '\n');
        fgets(input, sizeof(input), stdin);
        size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
                input[len - 1] = '\0';
            }
        generateGraphFromChatbot(input);
        return 0;
    }
    
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
        printf("2. Dodaj krawędźie\n");
        printf("3. Usuń krawędź\n");
        printf("4. Wyświetl graf\n");
        printf("5. Zapisz graf do pliku\n");
        printf("6. Wczytaj graf z pliku\n");
        printf("7. Stwórz graf przy pomocy graphviz\n");
        printf("8. Wyjście\n");
        printf("Wybór: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                freeGraph(&graph);
                Graph graph;
                initializeGraph(&graph, numVertices);
                generateRandomGraph(&graph);
                break;
            case 2:
                printf("Podawaj krawędzie (źródło, cel), wpisz -1 -1 aby zakończyć:\n");
                while (1) {
                    scanf("%d %d", &src, &dest);
                    if (src == -1 && dest == -1) {
                        break;
                    }
                    addEdge(&graph, src, dest);
                }
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
                printf("Podaj nazwe pliku do którego chcesz zapisać graf: ");
                scanf("%s", nazwa_pliku);
                saveGraphToFile(&graph, nazwa_pliku);
                break;
            case 6:
                printf("Podaj nazwe pliku z którego chcesz wczytać graf: ");
                scanf("%s", nazwa_pliku);
                loadGraphFromFile(&graph, nazwa_pliku);
                break;
            case 7:
                exportGraphToDOT(&graph, "graf.dot");
                generateGraph("graf.dot");
                break;
            case 8:
                freeGraph(&graph);
                return 0;
            
            default:
                printf("Nieprawidłowy wybór!\n");
        }
    }
    return 0;
}