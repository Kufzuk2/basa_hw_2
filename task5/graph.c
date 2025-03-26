#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct list_t {
    void*          data;
    struct list_t* next;
} list_t;

typedef struct Node {
    char*          id;

    list_t*  in_edges;
    list_t* out_edges;
} Node;

typedef struct Edge {
    struct Node*   from;
    struct Node*     to;
    int          weight;
} Edge;

typedef struct Graph {
    list_t* nodes;
} Graph;

Graph* create_graph() {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph -> nodes = NULL;
    return graph;
}

Node* find_node(Graph* graph, const char* id) {
    list_t* current = graph -> nodes;
    while (current != NULL) {
        Node* node = (Node*)current -> data;
        if (strcmp(node -> id, id) == 0) {
            return node;
        }
        current = current -> next;
    }
    return NULL;
}

void add_node(Graph* graph, const char* id) {
    if (find_node(graph, id) != NULL) {
        return; 
    }

    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node -> id        = strdup(id);
    new_node -> in_edges  =       NULL;
    new_node -> out_edges =       NULL;

    list_t* new_list_node = (list_t*)malloc(sizeof(list_t));

    new_list_node -> data =       new_node;
    new_list_node -> next = graph -> nodes;
    graph -> nodes        =  new_list_node;
}

void add_edge(Graph* graph, const char* from_id, const char* to_id, int weight) {
    Node* from = find_node(graph, from_id);
    Node* to   = find_node(graph,   to_id);

    if (from == NULL && to == NULL) {
        printf("Unknown nodes %s %s\n", from_id, to_id);
        return;
    }
    if (from == NULL) {
        printf("Unknown node %s\n", from_id);
        return;
    }
    if (to == NULL) {
        printf("Unknown node %s\n", to_id);
        return;
    }

    Edge* edge = (Edge*) malloc(sizeof(Edge));
    edge -> from   = from;
    edge -> to     = to;
    edge -> weight = weight;

    list_t* out_edge_node = (list_t*)malloc(sizeof(list_t));

    out_edge_node -> data =              edge;
    out_edge_node -> next = from -> out_edges;
    from -> out_edges     =     out_edge_node;


    list_t* in_edge_node = (list_t*)malloc(sizeof(list_t));

    in_edge_node -> data =           edge;
    in_edge_node -> next = to -> in_edges;
    to -> in_edges       =   in_edge_node;
}

void remove_edge_helper(Node* from, Node* to) {
    list_t** curr = &from -> out_edges;

    while (*curr != NULL) {
        Edge* edge = (Edge*)(*curr) -> data;

        if (edge -> to == to) {
            list_t* to_remove = *curr;
            *curr = to_remove -> next;

            free(     edge);
            free(to_remove);
            break;
        }
        curr = &(*curr) -> next;
    }
}

void remove_edge(Graph* graph, const char* from_id, const char* to_id) {
    Node* from = find_node(graph, from_id);
    Node* to = find_node(graph, to_id);

    if (from == NULL && to == NULL) {
        printf("Unknown nodes %s %s\n", from_id, to_id);
        return;
    }
    if (from == NULL) {
        printf("Unknown node %s\n", from_id);
        return;
    }
    if (to == NULL) {
        printf("Unknown node %s\n", to_id);
        return;
    }

    remove_edge_helper(from, to);

    remove_edge_helper(to, from);
}

void remove_node(Graph* graph, const char* id) {
    Node* node = find_node(graph, id);
    if (node == NULL) {
        printf("Unknown node %s\n", id);
        return;
    }

    list_t* in_edge = node -> in_edges;
    while (in_edge != NULL) {
        Edge* edge = (Edge*)in_edge -> data;
        list_t* next = in_edge -> next;
        remove_edge(graph, edge -> from -> id, id);
        in_edge = next;
    }

    list_t* out_edge = node -> out_edges;
    while (out_edge != NULL) {
        Edge* edge = (Edge*)out_edge -> data;
        list_t* next = out_edge -> next;
        remove_edge(graph, id, edge -> to -> id);
        out_edge = next;
    }

    list_t** curr = &graph -> nodes;
    while (*curr != NULL) {
        if ((*curr) -> data == node) {
            list_t* to_remove = *curr;
            *curr = to_remove -> next;
            free(node -> id);
            free(node);
            free(to_remove);
            return;
        }
        curr = &(*curr) -> next;
    }
}

void dfs_rpo(Node* node, list_t** result, bool* has_loop, char* loop_from, char* loop_to, bool* visited, bool* temp_marked) {
    if (temp_marked[(int)node -> id[0] - 'A']) {
        *has_loop = true;
        strcpy(loop_from, node -> id);
        return;
    }
    if (visited[(int)node -> id[0] - 'A']) {
        return;
    }

    temp_marked[(int)node -> id[0] - 'A'] = true;

    list_t* edge = node -> out_edges;
    while (edge != NULL) {
        Edge* e = (Edge*)edge -> data;
        dfs_rpo(e -> to, result, has_loop, loop_from, loop_to, visited, temp_marked);
        if (*has_loop && strlen(loop_to) == 0) {
            strcpy(loop_to, e -> to -> id);
        }
        edge = edge -> next;
    }

    visited[(int)node -> id[0] - 'A'] = true;
    temp_marked[(int)node -> id[0] - 'A'] = false;

    list_t* new_node = (list_t*)malloc(sizeof(list_t));
    new_node -> data = node;
    new_node -> next = *result;
    *result = new_node;
}

void reverse_list(list_t** head) {
    list_t* prev = NULL;
    list_t* current = *head;
    list_t* next = NULL;
    while (current != NULL) {
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void rpo_numbering(Graph* graph, const char* start_id) {
    Node* start = find_node(graph, start_id);
    if (start == NULL) {
        printf("Unknown node %s\n", start_id);
        return;
    }

    list_t* result = NULL;
    bool has_loop = false;
    char loop_from[10] = {0};
    char loop_to[10] = {0};
    bool visited[26] = {false};
    bool temp_marked[26] = {false};

    dfs_rpo(start, &result, &has_loop, loop_from, loop_to, visited, temp_marked);

    if (has_loop) {
        printf("Found loop %s -> %s\n", loop_from, loop_to);
    }

    reverse_list(&result);

    list_t* current = result;
    while (current != NULL) {
        Node* node = (Node*)current -> data;
        printf("%s ", node -> id);
        current = current -> next;
    }
    printf("\n");

    while (result != NULL) {
        list_t* temp = result;
        result = result -> next;
        free(temp);
    }
}

void free_graph(Graph* graph) {
    list_t* node = graph -> nodes;
    while (node != NULL) {
        Node* n = (Node*)node -> data;
        
        list_t* edge = n -> out_edges;
        while (edge != NULL) {
            list_t* temp = edge;
            edge = edge -> next;
            free(temp -> data);
            free(temp);
        }
        
        edge = n -> in_edges;
        while (edge != NULL) {
            list_t* temp = edge;
            edge = edge -> next;
            free(temp);
        }
        
        free(n -> id);
        free(n);
        
        list_t* temp = node;
        node = node -> next;
        free(temp);
    }
    free(graph);
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("Failed to open input file");
        return 1;
    }

    Graph* graph = create_graph();
    char command[20], arg1[20], arg2[20];
    int weight;

    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "NODE") == 0) {
            fscanf(file, "%s", arg1);
            add_node(graph, arg1);
        }
        else if (strcmp(command, "EDGE") == 0) {
            fscanf(file, "%s %s %d", arg1, arg2, &weight);
            add_edge(graph, arg1, arg2, weight);
        }
        else if (strcmp(command, "REMOVE") == 0) {
            fscanf(file, "%s", command);
            if (strcmp(command, "NODE") == 0) {
                fscanf(file, "%s", arg1);
                remove_node(graph, arg1);
            }
            else if (strcmp(command, "EDGE") == 0) {
                fscanf(file, "%s %s", arg1, arg2);
                remove_edge(graph, arg1, arg2);
            }
        }
        else if (strcmp(command, "RPO_NUMBERING") == 0) {
            fscanf(file, "%s", arg1);
            rpo_numbering(graph, arg1); 
        }
    }

    fclose(file);
    free_graph(graph);
    return 0;
}