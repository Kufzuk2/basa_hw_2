#include "list.c"
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
void history() {
    
    list* history = (list*) malloc(sizeof(list)); 
    list* future  = (list*) malloc(sizeof(list)); 

    char* cur_page = "homepage";

    char* str1;
    char* str2;

    char* back_str    =     "back";
    char* visit_str   =    "visit";
    char* forward_str = "fowrward";

    history = add(NULL, cur_page);

    int input_v = 1; 

    while (input_v) {
        int input_v = scanf("%s %s\n", str1, str2); 
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
                future  -> next_ = history;
                history = history -> prev_;

                future -> next_ -> prev_ = future;
                history -> next_ = NULL;

                future = future -> next_;
            }
        }
        else if (!(strcmp(str1, forward_str)))
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
}
