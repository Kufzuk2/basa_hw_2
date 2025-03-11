#pragma once


#include <stdio.h>
#include <stdlib.h>

typedef struct list{

    struct list* prev_;
    struct list* next_;
    node_t*      node_;

} list;


list*       add (list* cur_node, node* node);

void  pop_teil (list* head);

list* find_head (list* cur_node);

int    if_empty (list* node);

void print_node (list* node);   
