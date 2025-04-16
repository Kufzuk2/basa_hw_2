#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sort2.h"



#define MAX_DIGITS 10

int get_digit(const char* num_str, int pos) 
 {
    int len = strlen(num_str);
    
    if (pos >= len) 
        return 0;

    return num_str[len - 1 - pos] - '0';
}

int find_max_digits(list* head) 
    {
    int max = 0;
    list* curr = head;
    while (curr) {
        int len = strlen(curr->data_);
        if (len > max) max = len;
        curr = curr->next_;
    }
    return max;
}

list* radix_sort(list* head) {
    if (!head || !head->next_) return head;

    int max_digits = find_max_digits(head);
    
    for (int d = 0; d < max_digits; d++) {
        list* buckets[10] = {NULL};
        list* tails[10] = {NULL};
        
        list* curr = head;
        while (curr) {
            int digit = get_digit(curr->data_, d);
            list* next = curr->next_;
            
            curr->prev_ = NULL;
            curr->next_ = NULL;
            
            if (!buckets[digit]) {
                buckets[digit] = tails[digit] = curr;
            } else {
                tails[digit]->next_ = curr;
                curr->prev_ = tails[digit];
                tails[digit] = curr;
            }
            
            curr = next;
        }
        
        head = NULL;
        list* tail = NULL;
        
        for (int i = 0; i < 10; i++) {
            if (buckets[i]) {
                if (!head) {
                    head = buckets[i];
                    tail = tails[i];
                } else {
                    tail->next_ = buckets[i];
                    buckets[i]->prev_ = tail;
                    tail = tails[i];
                }
            }
        }
    }
    
    return head;
}
