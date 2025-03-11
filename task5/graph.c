#include <stdio.h>

typedef struct node_t {
    list*   in_edges_;
    list*  out_edges_;
    list*  all_nodes_;

    int    child_num_;
    char*       name_;
    int     node_num_;
    int           id_;

} node_t;

typedef struct edge_t  {
    node*  node_from_;
    node*  node_to_  ; 
    int       weight_;  // > 0

} edge_t;


node_t* add_node(char* name, node_t* graph) {
    if (!name) {
        printf("incorrect name for node given \n");
        return NULL;
    }

        node_t* node  = (node_t*) calloc(sizeof(node_t), 1);
        node -> name_ = strdup(name);

        add(graph -> all_nodes_, node);

        if (!(node -> all_nodes_ -> left_)) {
            node -> node_num_ = 1;
            return node;
        }

        node_t* cur_node = node;

        do {
            (node -> node_num_)++;
        }
        while (cur_node -> all_nodes_ -> left_);


        return node;
}

edge_t* add_edge(node_t* node_from, node_t* node_to, int weight) {
    if (!node_from){
        printf("No node from \n");
        return NULL;
    }

    if (!node_to){
        printf("No node to   \n");
        return NULL;
    }    

    ///
    ///  CHECK IF EDGE ALREADY EXISTS
    ///

    edge_t* edge = (edge_t*) calloc(sizeof(edge_t), 1);

    edge -> node_from_ = node_from_;
    edge -> node_to_   = node_to_  ;
    edge -> weight_    = weight_   ;

    (node_from -> child_num_)++    ; 

    add(node_from -> out_edges_, edge);
    add(node_to   ->  in_edges_, edge);
    //check for 
}












