#include "list.h"
#include <string.h>
#include "web_his.h"


void go_back(list** history, list** future) {
    if (!(*future)) {
        *future = *history;
        (*history) = (*history) -> prev_;
        (*history) -> next_ = NULL;
        (*future ) -> prev_ = NULL;
    }
    else {
        (*future ) -> next_ = *history;
        (*history) = (*history) -> prev_;

        (*history) -> next_ -> prev_ = *future;
        (*history) -> next_  = NULL;  
        (*future ) = (*future ) -> next_;
    }
}


void go_forward(list** history, list** future) {

    if (!(*future) -> prev_) {
        (*history) -> next_  =  *future;
        (*future ) -> prev_  =  *history;
        (*history) = *future;
        *future = NULL;
        return;
    }


    (*history) ->   next_           =   *future;
    (*future ) =  (*future )       ->     prev_;
    (*future ) ->   next_ -> prev_  =  *history;
    (*history) =  (*future )       ->     next_;
    (*future ) ->   next_           =      NULL;

}





void history() {
    
    list* history = (list*) malloc(sizeof(list)); 
    list* future  = (list*) malloc(sizeof(list)); 

    char* cur_page = "homepage";

    char str1[256];
    char str2[256];

    char* back_str    =     "back";
    char* visit_str   =    "visit";
    char* forward_str =  "forward";

    history = add(NULL, cur_page);
    future = NULL;

    int input_v = scanf("%s %s", str1, str2); 


    while (input_v != 0) {
         
        int jmp = 0;

        if (!strcmp(str1, visit_str)) {
            pop_teil(future);
            future = NULL;


            history = add(history, str2); 
          
        }
        else if (!strcmp(str1, back_str)) {
            jmp = strtoll(str2, NULL, 0);

            for (int i = 0; i < jmp; i++) {
                if (history -> prev_ == NULL) 
                    break;
                
                go_back(&history, &future);
            }
        }
        else if (!(strcmp(str1, forward_str))){
            jmp = strtoll(str2, NULL, 0);
            
            for (int i = 0; i < jmp; i++) {
                if (future == NULL)
                    break;
                go_forward(&history, &future);
            }
        }
        else{
            printf("<%s> is an unknown command, try again \n", str1);
            input_v = scanf("%s %s", str1, str2);
            continue;
        }

        printf("%s \n", history -> data_);
        printf("\n");
        

        input_v = scanf("%s %s", str1, str2);
    }
    // need mem clean

    pop_teil(history);
    pop_teil(future );

}
