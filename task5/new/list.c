#include "list.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


list* add(list* cur_node, node_t* node) {
    
    list* new_node = (list*) calloc(sizeof(list), 1);

    if (!new_node)
        return NULL;

    
    new_node -> next_ = NULL; // probably already null after calloc???
    new_node -> node_ = strdup(node);

    if (!cur_node) 
        new_node -> prev_ = NULL;
    else
        cur_node -> next_ = new_node;

    new_node -> prev_ = cur_node;

    return new_node;
}



void pop_teil (list* head) {
    list* temp;  
    while (head) {
        temp = head;
        head = head->next_; 


        if (temp->node_) {
            free(temp->node_);
        }

        free(temp);
    }
}


int if_empty (list* node) {
    return (!(node -> prev_) && !(node -> next_)) ?
                                                1 :
                                                0 ;
}


void print_node (list* node) {
    if (!node) {
        printf("nothing to print \n");
        return;
    }
    printf("%s \n", node -> node_);
}

list* find_head (list* cur_node) {
    list* node = cur_node;

    while (node -> prev_) 
        node = node -> prev_;

    return node;
}



