
#include "queue.h"

queue* add_elem(queue* end, char* data)
{

    if (!data){
        printf("data is empty \n");
        return end;
    }


    queue* cur_obj = (queue*) malloc(sizeof(queue));
    if (!cur_obj)
    {
        printf("problems with memory allocation in add_elem funtion \n");
        return NULL;
    }


    cur_obj->next_  =  NULL;
    cur_obj->data_  =  data;

    if (end)        
        end->next_ = cur_obj;

    return cur_obj;
}


queue* dequeue(queue* front)
{
    if (!front)
        return front;       

    queue* new_front = front->next_;
    free(front);
    return new_front;
}


void kill_queue(queue* front){
    if (!front)
        return NULL;

    queue* cur_obj = front;
    queue*    next = front->next_;

    while (next) {
        cur_obj->data_ = NULL;
        free(cur_obj);

        cur_obj = next;
        next = next->next_;
    }
}


void q_print(queue* front)   // prints queue
{
    if (!front->next_)
        return;

    queue* cur_elem = front->next_;
    
    while (cur_elem)
    {
        printf("%s ", cur_elem->data_);
        cur_elem = cur_elem->next_;
    }
    printf("\n");
}
