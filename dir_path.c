
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
            // Валидное имя директории или файла
            append(list, dir);
        }
        dir = strtok(NULL, delimiter);

}
















