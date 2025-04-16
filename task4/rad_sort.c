#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int get_digit(int num, int exp) {
    return (num / exp) % 10;
}

void radix_sort(int* arr, int n) {
    if (n <= 1) return;
    
    int max_num = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_num) 
            max_num = arr[i];
    }
    
    int exp = 1;
    int* output = malloc(n * sizeof(int));
    int count[10];
    
    while (max_num / exp > 0) {
        memset(count, 0, 10 * sizeof(int));
        
        for (int i = 0; i < n; i++) 
            count[get_digit(arr[i], exp)]++;
        
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        
        for (int i = n - 1; i >= 0; i--) {
            int digit = get_digit(arr[i], exp);
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
        memcpy(arr, output, n * sizeof(int));
        exp *= 10;
    }
    
    free(output);
}

void process_file(const char* input_filename, const char* output_filename) {
    FILE* input = fopen(input_filename, "r");
    FILE* output = fopen(output_filename, "w");
    
    if (!input || !output) {
        printf("Error opening files\n");
        if (input) fclose(input);
        if (output) fclose(output);
        return;
    }

    char line[1000000]; 
    while (fgets(line, sizeof(line), input)) {
        if (line[0] == '\n') continue;
        
        char* line_start = line;
        
        int first_num;
        if (sscanf(line_start, "%d", &first_num) != 1) {
            continue;
        }
        
        while (*line_start && *line_start != ' ') line_start++;
        while (*line_start == ' ') line_start++;
        
        int count = 0;
        char* ptr = line_start;
        while (*ptr) {
            if (isdigit(*ptr)) {
                count++;
                while (isdigit(*ptr)) ptr++;
            }
            ptr++;
        }
        if (count == 0) continue;
        
        int* arr = malloc(count * sizeof(int));
        ptr = line_start;
        for (int i = 0; i < count; i++) {
            while (*ptr && !isdigit(*ptr)) ptr++;
            if (!*ptr) break;
            arr[i] = atoi(ptr);
            while (isdigit(*ptr)) ptr++;
        }
        
        clock_t start = clock();
        radix_sort(arr, count);
        clock_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        
        fprintf(output, "%d %.6f\n", first_num, time);
        
        free(arr);
    }
    
    fclose(input);
    fclose(output);
}   

int main() {
    process_file("text_data/input_size.txt", "text_data/c_size.txt");
    process_file("text_data/input_unsort.txt", "text_data/c_unsort.txt");
    process_file("text_data/input_radix.txt", "text_data/c_radix.txt");

    return 0;
}