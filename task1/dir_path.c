#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define PATH_MAX 4096
#define MAX_DIRS 1024 

char* simpl_path(char* path) 
{
    char* components[MAX_DIRS];
    int top = -1;  

    char* token = strtok(path, "/");
    while (token != NULL) 
    {
        if (strcmp(token, "..") == 0) 
        {
            if (top >= 0) 
                free(components[top--]);
        } 
        else if (strcmp(token, ".") != 0 && strlen(token) > 0) 
        {
            if (top + 1 >= MAX_DIRS) 
            {
                fprintf(stderr, "Path is too deep\n");
                return NULL;
            }

            components[++top] = strdup(token);
            if (components[top] == NULL) 
            {
                fprintf(stderr, "Memory allocation failed\n");
                return NULL;
            }
        }
        token = strtok(NULL, "/");
    }

    char* result = malloc(PATH_MAX);
    if (result == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    result[0] = '\0';

    if (top == -1) 
        strcpy(result, "/");
    else 
    {
        for (int i = 0; i <= top; i++) 
        {
            strcat(result, "/");
            strcat(result, components[i]);
            free(components[i]);  
        }
    }

    return result;
}

int main()
{
    char path[PATH_MAX];
    if (fgets(path, PATH_MAX, stdin) == NULL) 
        return 1;
    

    path[strcspn(path, "\n")] = '\0';

    char* canon_path = simpl_path(path);
    
    if (canon_path != NULL) {
        printf("%s\n", canon_path);
        free(canon_path);
    } else 
        return 1;

    return 0;
}