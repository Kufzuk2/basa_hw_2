#include "list.h"
#include <string.h>

/*
list* move_back (list* history, list* future, int jmp) {
    if (!history)
        return NULL;
    
    list* cur_obj = history;

    for (int i = 0; i < jmp; i++) {
        furure  = add(history, history->data_); // history  must be the last
        history = delist(history); 

    }
    
    while (cur_obj ->)
}
*/

void go_back(list** history, list** future) {
    // history -> prev_  != NULL
    

    if (!(*future)) {
        printf(" no future \n");
        *future = *history;
        (*history) = (*history) -> prev_;
        (*history) -> next_ = NULL;
        (*future ) -> prev_ = NULL;
    }
    else {
        printf(" future exists \n");
        (*future ) -> next_ = *history;
        (*history) = (*history) -> prev_;

        (*history) -> next_ -> prev_ = *future;
        (*history) -> next_  = NULL;  
        (*future ) = (*future ) -> next_;
    }

    /*
    (*history) = (*history) -> prev_;
    printf(" back here \n");
   
    if (!((*future) -> next_))
        (*future) -> next_ -> prev_ = (*future);
    else
        (*future) ->          prev_ = (*future);

    (*history) -> next_ = NULL;

   
    (*future) = (*future) -> next_;    
*/


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

    int input_v = scanf("%s %s", str1, str2); 
    //printf(" scanf = %d \n", input_v);


    while (input_v != 0) {
         
        int jmp = 0;
        printf(" while here \n");

        if (!strcmp(str1, visit_str)) {
            pop_teil(future);
            future = NULL;
        //    printf(" visit here \n");

            history = add(history, str2); 
        }
        else if (!strcmp(str1, back_str)) {
            //printf(" back here \n");
            jmp = strtoll(str2, NULL, 0);
            //printf(" back here \n");

            for (int i = 0; i < jmp; i++) {
                if (history -> prev_ == NULL)
                    break;
                printf(" back here 1\n");

                go_back(&history, &future);

                printf ("data = %s \n", history -> data_);
/*
                if (!future)
                    future = history;
                else
                    future  -> next_ = history;

                history = history -> prev_;
                printf(" back here \n");
                if (!(future -> next_))
                    future -> next_ -> prev_ = future;
                else
                    future          -> prev_ = future;

                history -> next_ = NULL;

                if (!future)
                    future = future -> next_;    */
                
            }
        }
        else if (!(strcmp(str1, forward_str))){
            printf(" forward here \n");
            jmp = strtoll(str2, NULL, 0);
            
            for (int i = 0; i < jmp; i++) {
                if (future -> prev_ == NULL)
                    break;

                history  -> next_ = future;
                future = future -> prev_;

                history -> next_ -> prev_ = history;
                future -> next_ = NULL;

                history = history -> next_;
            }
        }

        printf("%s \n", history -> data_);

        input_v = scanf("%s %s", str1, str2);
    }
}
