#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sort2.h"

int main() {
    srand(time(NULL));

    for (int i = 0; i < 2; i++)
        make_test(20, 3);
    
    FILE* output_file1 = fopen("time_deg.txt", "w");
    if (!output_file1) {
        printf("Failed to create file.\n");
        return 1;
    }

    FILE* output_file2 = fopen("time_size.txt", "w");
    if (!output_file2) {
        printf("Failed to create file.\n");
        return 1;
    }
    

    test_sorted_degree(20000, output_file1);
    time_cmp_test     (       output_file2);
}


