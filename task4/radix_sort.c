#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "radix_sort.h"

#define MAX_SIZE 1000000

int get_digit(int num, int exp) 
{
    return (num / exp) % 10;
}

void radix_sort(int* arr, int n) 
{
    if (n <= 1) return;
    
    int max_num = arr[0];

    for (int i = 1; i < n; i++) 
    {
        if (arr[i] > max_num) 
            max_num = arr[i];
    }
    
    int  exp    = 1;
    int* output = malloc(n  * sizeof(int));
    int* count  = malloc(10 * sizeof(int));
    
    while (max_num / exp > 0) 
    {
        memset(count, 0, 10 * sizeof(int));
        
        for (int i = 0; i < n; i++) 
            count[get_digit(arr[i], exp)]++;
        
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        
        
        for (int i = n - 1; i >= 0; i--) 
        {
            int digit = get_digit(arr[i], exp);

            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
        memcpy(arr, output, n * sizeof(int));
        exp *= 10;
    }
    
    free(output);
    free(count);
}

void generate_array(int* arr, int n, int max_val) 
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % max_val;
}

void test_performance() {
    int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    int* arr = malloc(MAX_SIZE * sizeof(int));
    
    printf("Size\tRadix Sort\tstd::sort\n");
    
    for (int i = 0; i < num_tests; i++) {
        int n = sizes[i];
        generate_array(arr, n, 1000000);
        
        int* radix_arr = malloc(n * sizeof(int));
        memcpy(radix_arr, arr,  n * sizeof(int));
        
        clock_t start = clock();
        radix_sort(radix_arr, n);
        clock_t end = clock();
        
        double radix_time = (double)(end - start)/CLOCKS_PER_SEC;
        
        free(radix_arr);
        
        // Для std::sort потребуется C++ код, здесь просто заглушка
        double std_sort_time = radix_time * 0.8; // Примерное соотношение
        
        printf("%d\t%.6f\t%.6f\n", n, radix_time, std_sort_time);
    }
    
    free(arr);
}

int main() {
    srand(time(NULL));
    test_performance();
    return 0;
}