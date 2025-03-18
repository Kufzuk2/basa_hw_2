#pragma once
#include "list.h"


typedef struct node {
    char* id; // Уникальный идентификатор узла
    list* in_edges; // Список входящих рёбер
    list* out_edges; // Список исходящих рёбер
} node_t;

typedef struct edge {
    node_t* from; // Узел-предшественник
    node_t* to;   // Узел-преемник
    int weight;    // Вес ребра
} edge_t;

typedef struct graph {
    list* nodes; // Список всех узлов
} graph_t;


graph_t* create_graph();

void     add_edge      (graph_t* graph, const char*  from_id, const char* to_id, int weight);
void     remove_edge   (graph_t* graph, const char*  from_id, const char* to_id            );
void     rpo_numbering (graph_t* graph, const char* start_id                               );

node_t*  add_node      (graph_t* graph, const char* id                                     );      
void     remove_node   (graph_t* graph, const char* id                                     );       
  
void     print_graph   (graph_t* graph                                                     ); 