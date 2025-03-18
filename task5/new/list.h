#pragma once


#include <stdio.h>
#include <stdlib.h>

struct node_t;

typedef struct list{

    struct list* prev_;
    struct list* next_;
    node_t*      node_;

} list;


list*   add (list* cur_node, node_t* node);

void  pop_teil (list* head);

list* find_head (list* cur_node);

int    if_empty (list* node);

void print_node (list* node);   
