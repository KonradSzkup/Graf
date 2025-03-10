#ifndef LLM_GRAPH_H
#define LLM_GRAPH_H

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);
char* extract_full_response(const char *json_stream);
void generateGraphFromChatbot(const char *prompt);


#endif