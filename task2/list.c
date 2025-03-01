#include "list.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


list* add(list* cur_node, char* data) {
    
    list* new_node = (list*) calloc(sizeof(list), 1);

    if (!new_node)
        return NULL;

    
    new_node -> next_ = NULL; // probably already null after calloc???
    new_node->data_ = strdup(data);

    if (!cur_node) 
        new_node -> prev_ = NULL;
    else
        cur_node -> next_ = new_node;

    new_node -> prev_ = cur_node;

    return new_node;
}



list*  pop_teil (list* cur_node) {

    if (!cur_node)
        return NULL;

    list* prev = cur_node -> prev_;
    if ((cur_node -> next_) == NULL) {

        cur_node      -> data_ = NULL;
        cur_node      -> prev_ = NULL;

        free(cur_node -> data_)      ;
//        free(cur_node -> prev_)      ;

        return prev;
    }

    pop_teil(cur_node -> next_);

    return prev;
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
    printf("%s \n", node -> data_);
}

list* find_head (list* cur_node) {
    list* node = cur_node;

    while (node -> prev_) 
        node = node -> prev_;

    return node;
}


void kill_list(list* cur_node) {
    list* head = find_head(cur_node);
    
    if (pop_teil(head))
        printf("problems wirh list destruction \n");
    
}

