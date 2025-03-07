#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "graph.h"

#define API_KEY "sk-...XE4A"
#define API_URL "https://api.openai.com/v1/chat/completions"

// Struktura do przechowywania odpowiedzi API
struct Memory {
    char* response;
    size_t size;
};

// Callback do zapisu odpowiedzi API
static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    struct Memory* mem = (struct Memory*)userp;

    char* ptr = realloc(mem->response, mem->size + totalSize + 1);
    if (ptr == NULL) return 0;

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), contents, totalSize);
    mem->size += totalSize;
    mem->response[mem->size] = '\0';

    return totalSize;
}

// Funkcja pobierająca odpowiedź z LLM
void chatWithLLM() {
    CURL* curl;
    CURLcode res;
    struct Memory chunk = { .response = malloc(1), .size = 0 };

    if (!chunk.response) {
        printf("Błąd alokacji pamięci\n");
        return;
    }

    char userInput[256];
    printf("Wpisz zapytanie do LLM: ");
    getchar();  // Wyczyść bufor
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = 0; // Usuń nową linię

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        char postData[1024];
        snprintf(postData, sizeof(postData), 
            "{ \"model\": \"gpt-4\", \"messages\": [ { \"role\": \"user\", \"content\": \"%s\" } ] }", 
            userInput);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer " API_KEY);

        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            printf("Błąd zapytania do API: %s\n", curl_easy_strerror(res));
        } else {
            printf("\n💬 Odpowiedź LLM:\n%s\n", chunk.response);
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    free(chunk.response);
    curl_global_cleanup();
}