
#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    struct queue*  next_;
    char*          data_;

} queue;


queue* add_elem(queue* end, cahr* data);

queue* dequeue(queue* front);

void q_print(queue* front);
