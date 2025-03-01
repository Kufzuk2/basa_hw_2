
#include "list.h"
#include <string.h>


int main(){

    max_len = 4096;
    char  input_path [max_len + 1];
    char output_path [max_len + 1];
    
    fgets(input, max_len, stdin);
    input[strcspn(input, "\n")] = '\0';
`
    get_path(input_path, output_path);

    printf("%s \n", output_path);
}

/*
void get_path(char* input_path, char* output_path){

    char* div = "/";
    if (!strcmp(input_path[0], '/')) {
        printf("path must start from '/' \n");
        return;
    }
    list* path = (list*) malloc(sizeof(list)); 
   

    char* dir;
    char* path_copy = strdup(path); 
    dir = strtok(path_copy, delimiter);

    while (dir) {
        if (strcmp(dir, ".") == 0) {

        } else if (strcmp(dir, "..") == 0) {
            if (list->head != NULL) {
                remove_last(list);
            } else {
                printf("Going upper than the root directory is not possible.\n");
                free(path_copy);
                free_list(list);
                return "/";
            }
        } else {
            add(list, dir);
        }
        dir = strtok(NULL, delimiter);
    }
}

*/



void add_dir(list** path, char* dir) {
    if (!dir || strlen(dir) == 0) 
        return;

    *path = add(*path, strdup(dir));
}


void pop_dir(list** path) {   // kill list 
    if (*path == NULL) 
        return;

    list* tmp = *path;
    *path = (*path)->prev_;
    free(tmp->data_);
    free(tmp);
}




char* get_path(char* init_path) {
    list* path = NULL;

    char* path_copy = strdup(init_path);
    char* token     = strtok(path_copy, "/");

    while (token != NULL) {
        if (!strcmp(token, ".")) {}

        else if (!strcmp(token, "..")) {
            if (path == NULL) {
                printf("Going upper than the root directory is not possible.\n");

                free(path_copy);
                kill_list(path);

                return "/";
            }
            
            pop_dir(&path);
        } 
        else {
            add_dir(&path, token);
        }

        token = strtok(NULL, "/");
    }


    char  path[PATH_MAX];
    out_path[0]   = '\0'; 

    list* current = path;

    while (current) {
        if (strlen(out_path) > 0) {
            strcat(out_path, "/");
        }
        strcat(out_path, current->data_);
        current = current->prev_;
    }

    if (strlen(out_path) == 0) {
        strcpy(out_path, "/");
    }

    free(path_copy);
    kill_list(path);

    return strdup(out_path);
}


