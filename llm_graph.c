#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

#define API_URL "http://localhost:11434/api/generate"

// Bufor do przechowywania odpowiedzi API
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Funkcja do zapisywania odpowiedzi API w pamięci
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userdata;

    char *new_memory = realloc(mem->memory, mem->size + total_size + 1);
    if (new_memory == NULL) {
        printf("Błąd alokacji pamięci!\n");
        return 0;
    }

    mem->memory = new_memory;
    memcpy(&(mem->memory[mem->size]), ptr, total_size);
    mem->size += total_size;
    mem->memory[mem->size] = '\0';  // Dodanie zakończenia stringa

    return total_size;
}

// Funkcja do parsowania JSON i wyciągania odpowiedzi
char* extract_full_response(const char *json_stream) {
    // Bufor na pełną odpowiedź
    size_t buffer_size = 1024;  // Początkowy rozmiar bufora
    char *full_response = (char*)calloc(buffer_size, 1);  // Zapasowe 1024 bajty
    if (!full_response) {
        return strdup("Memory allocation error");
    }

    // Tymczasowy bufor na pojedynczą linię JSON
    char *json_copy = strdup(json_stream);
    if (!json_copy) {
        free(full_response);
        return strdup("Memory allocation error");
    }

    // Podział strumienia na linie (każda linia to osobny JSON)
    char *line = strtok(json_copy, "\n");
    while (line != NULL) {
        cJSON *root = cJSON_Parse(line);
        if (!root) {
            free(json_copy);
            free(full_response);
            return strdup("Error parsing JSON");
        }

        // Sprawdzenie, czy odpowiedź jest obiektem
        if (cJSON_IsObject(root)) {
            cJSON *response = cJSON_GetObjectItem(root, "response");
            if (response && cJSON_IsString(response)) {
                // Sprawdzenie, czy bufor jest wystarczająco duży
                size_t response_len = strlen(response->valuestring);
                size_t current_len = strlen(full_response);

                if (current_len + response_len + 1 > buffer_size) {
                    buffer_size = current_len + response_len + 1;
                    char *new_buffer = (char*)realloc(full_response, buffer_size);
                    if (!new_buffer) {
                        free(json_copy);
                        free(full_response);
                        cJSON_Delete(root);
                        return strdup("Memory allocation error");
                    }
                    full_response = new_buffer;
                }

                // Dodanie fragmentu odpowiedzi do pełnej odpowiedzi
                strcat(full_response, response->valuestring);
            }
        }

        cJSON_Delete(root);
        line = strtok(NULL, "\n");  // Przejście do następnej linii
    }

    free(json_copy);
    return full_response;
}

// Funkcja wysyłająca zapytanie do chatbota i zapisująca odpowiedź do pliku
void generateGraphFromChatbot(const char *prompt) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct response;
    response.memory = malloc(1);
    response.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        char post_data[512];
        snprintf(post_data, sizeof(post_data), "{\"model\": \"mistral\", \"prompt\": \"%s\"}", prompt);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Błąd zapytania do API: %s\n", curl_easy_strerror(res));
        } else {
            // Zapisujemy odpowiedź do pliku tekstowego
            FILE *file = fopen("graf.txt", "w");
            if (file) {
                fprintf(file, "%s\n", extract_full_response(response.memory));
                fclose(file);
                printf("Graf zapisany jako graf.txt\n");
            } else {
                printf("Błąd zapisu pliku graf.txt\n");
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    free(response.memory);
}


