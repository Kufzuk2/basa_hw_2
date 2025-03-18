#include "list.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


graph_t* create_graph() {
    graph_t* graph = (graph_t*) calloc(1, sizeof(graph_t));
    if (!graph) return NULL;
    graph->nodes = NULL;
    return graph;
}


node_t* add_node(graph_t* graph, const char* id) {
    if (!graph || !id) return NULL;

    // Проверяем, существует ли уже такой узел
    list* current = graph->nodes;
    while (current) {
        if (strcmp(current->node_->id, id) == 0) {
            printf("Node %s already exists\n", id);
            return NULL;
        }
        current = current->next_;
    }

    // Создаем новый узел
    node_t* new_node = (node_t*) calloc(1, sizeof(node_t));
    if (!new_node) return NULL;

    new_node->id = strdup(id);
    new_node->in_edges = NULL;
    new_node->out_edges = NULL;

    // Добавляем узел в список узлов графа
    graph->nodes = add(graph->nodes, new_node);
    return new_node;
}


void add_edge(graph_t* graph, const char* from_id, const char* to_id, int weight) {
    if (!graph || !from_id || !to_id || weight < 0) {
        printf("Invalid edge parameters\n");
        return;
    }

    // Находим узлы A и B
    node_t* from_node = NULL;
    node_t* to_node = NULL;

    list* current = graph->nodes;
    while (current) {
        if (strcmp(current->node_->id, from_id) == 0) {
            from_node = (node_t*) current->node_;
        }
        if (strcmp(current->node_->id, to_id) == 0) {
            to_node = (node_t*) current->node_;
        }
        if (from_node && to_node) break;
        current = current->next_;
    }

    if (!from_node) {
        printf("Unknown node %s\n", from_id);
        return;
    }
    if (!to_node) {
        printf("Unknown node %s\n", to_id);
        return;
    }

    // Создаем новое ребро
    edge_t* new_edge = (edge_t*) calloc(1, sizeof(edge_t));
    if (!new_edge) return;

    new_edge->from = from_node;
    new_edge->to = to_node;
    new_edge->weight = weight;

    // Добавляем ребро в списки входящих и исходящих рёбер
    from_node->out_edges = add(from_node->out_edges, new_edge);
    to_node->in_edges = add(to_node->in_edges, new_edge);
}


void remove_node(graph_t* graph, const char* id) {
    if (!graph || !id) {
        printf("Invalid node removal parameters\n");
        return;
    }

    // Находим узел для удаления
    list* current = graph->nodes;
    list* prev = NULL;

    while (current) {
        if (strcmp(((node_t*) current->node_)->id, id) == 0) {
            break;
        }
        prev = current;
        current = current->next_;
    }

    if (!current) {
        printf("Unknown node %s\n", id);
        return;
    }

    // Удаляем все исходящие и входящие рёбра
    list* edge_current = ((node_t*) current->node_)->out_edges;
    while (edge_current) {
        edge_t* edge = (edge_t*) edge_current->node_;
        // Удаляем ссылку на это ребро из списка входящих рёбер узла-преемника
        list* in_edge_current = edge->to->in_edges;
        list* in_edge_prev = NULL;
        while (in_edge_current) {
            if (in_edge_current->node_ == edge) {
                if (in_edge_prev) {
                    in_edge_prev->next_ = in_edge_current->next_;
                } else {
                    edge->to->in_edges = in_edge_current->next_;
                }
                free(in_edge_current);
                break;
            }
            in_edge_prev = in_edge_current;
            in_edge_current = in_edge_current->next_;
        }
        edge_current = edge_current->next_;
        free(edge);
    }

    // Удаляем сам узел
    if (prev) {
        prev->next_ = current->next_;
    } else {
        graph->nodes = current->next_;
    }
    free(((node_t*) current->node_));
    free(current);
}



void remove_edge(graph_t* graph, const char* from_id, const char* to_id) {
    if (!graph || !from_id || !to_id) {
        printf("Invalid edge removal parameters\n");
        return;
    }

    // Находим узлы A и B
    node_t* from_node = NULL;
    node_t* to_node = NULL;

    list* current = graph->nodes;
    while (current) {
        if (strcmp(current->node_->id, from_id) == 0) {
            from_node = (node_t*) current->node_;
        }
        if (strcmp(current->node_->id, to_id) == 0) {
            to_node = (node_t*) current->node_;
        }
        if (from_node && to_node) break;
        current = current->next_;
    }

    if (!from_node) {
        printf("Unknown node %s\n", from_id);
        return;
    }
    if (!to_node) {
        printf("Unknown node %s\n", to_id);
        return;
    }

    // Находим и удаляем ребро
    list* edge_current = from_node->out_edges;
    list* edge_prev = NULL;

    while (edge_current) {
        edge_t* edge = (edge_t*) edge_current->node_;
        if (edge->to == to_node) {
            if (edge_prev) {
                edge_prev->next_ = edge_current->next_;
            } else {
                from_node->out_edges = edge_current->next_;
            }
            free(edge_current);
            free(edge);
            break;
        }
        edge_prev = edge_current;
        edge_current = edge_current->next_;
    }
}



void rpo_numbering(graph_t* graph, const char* start_id) {
    if (!graph || !start_id) return;

    // Находим начальный узел
    node_t* start_node = NULL;
    list* current = graph->nodes;
    while (current) {
        if (strcmp(((node_t*) current->node_)->id, start_id) == 0) {
            start_node = (node_t*) current->node_;
            break;
        }
        current = current->next_;
    }

    if (!start_node) {
        printf("Unknown node %s\n", start_id);
        return;
    }

    // Выполняем DFS для получения RPO
    list* stack = NULL;
    list* visited = NULL;
    list* rpo = NULL;

    stack = add(stack, start_node);

    while (stack) {
        node_t* node = (node_t*) stack->node_;
        stack = stack->next_;

        if (find_in_list(visited, node)) continue;

        visited = add(visited, node);

        list* edge_current = node->out_edges;
        while (edge_current) {
            edge_t* edge = (edge_t*) edge_current->node_;
            if (!find_in_list(visited, edge->to)) {
                stack = add(stack, edge->to);
            }
            edge_current = edge_current->next_;
        }

        rpo = add(rpo, node);
    }

    // Разворачиваем RPO
    list* reversed_rpo = reverse_list(rpo);

    // Выводим результат
    current = reversed_rpo;
    while (current) {
        printf("%s ", ((node_t*) current->node_)->id);
        current = current->next_;
    }
    printf("\n");

    // Очищаем память
    pop_teil(stack);
    pop_teil(visited);
    pop_teil(rpo);
    pop_teil(reversed_rpo);
}




void print_graph(graph_t* graph) {
    if (!graph || !graph->nodes) {
        printf("Graph is empty\n");
        return;
    }

    // Проходим по всем узлам графа
    list* current_node = graph->nodes;
    while (current_node) {
        node_t* node = (node_t*) current_node->node_;
        printf("Node: %s\n", node->id);

        // Вывод исходящих рёбер
        if (node->out_edges) {
            printf("  Outgoing edges:\n");
            list* edge_current = node->out_edges;
            while (edge_current) {
                edge_t* edge = (edge_t*) edge_current->node_;
                printf("    -> %s (weight: %d)\n", edge->to->id, edge->weight);
                edge_current = edge_current->next_;
            }
        } else {
            printf("  No outgoing edges\n");
        }

        // Вывод входящих рёбер
        if (node->in_edges) {
            printf("  Incoming edges:\n");
            list* edge_current = node->in_edges;
            while (edge_current) {
                edge_t* edge = (edge_t*) edge_current->node_;
                printf("    <- %s (weight: %d)\n", edge->from->id, edge->weight);
                edge_current = edge_current->next_;
            }
        } else {
            printf("  No incoming edges\n");
        }

        current_node = current_node->next_;
    }
}


