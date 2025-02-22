#pragma once


#include <stdio.h>
#include <stdlib.h>

typedef struct list{

    struct list* prev_;
    struct list* next_;
    char*        data_;

} list;


list*       add (list* cur_node, char* data);

list*  pop_teil (list* cur_node);

list* find_head (list* cur_node);

int    if_empty (list* node);

void print_node (list* node);   

void  kill_list (list* cur_node);