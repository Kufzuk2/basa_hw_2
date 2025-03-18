#include <stdio.h>

#include "graph.h"
#include "list.h"


int main() {
    graph_t* graph = create_graph();

    // Добавление узлов
    add_node(graph, "A");
    add_node(graph, "B");
    add_node(graph, "C");

    // Добавление рёбер
    add_edge(graph, "A", "B", 5);
    add_edge(graph, "B", "C", 3);

    // RPO numbering
    rpo_numbering(graph, "A");

    // Удаление узла
    remove_node(graph, "B");

    print_graph(graph);

    // Очистка графа
    pop_teil(graph->nodes);
    free(graph);

    return 0;
}