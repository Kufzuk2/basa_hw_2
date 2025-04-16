#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int my_pow(int num, int pw) {
    int res = 1;
    while (pw > 0) {
        res *= num;
        pw--;
    }
    return res;
}

int check_if_sorted(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1])
            return 0;
    }
    return 1;
}

int* cp_arr(int* arr, int* new_arr, int size) {
    if (!arr)
        return NULL;
    
    for(int i = 0; i < size; i++) 
        new_arr[i] = arr[i];

    return new_arr;
}

int* sort2_sh(int* arr, int size){
    if (!arr){
        printf("empty arr \n");
        return NULL;
    }

    if (check_if_sorted(arr, size)) {
        return arr;
    }

    int iter_num = 0;

    while (iter_num * 2 < size) {
        for (int i = iter_num; i < size - iter_num - 1; i++) {
            if (arr[i] > arr[i + 1]){
                int tmp_int = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = tmp_int;
            }    
        }
        
        for (int j = size - iter_num - 1; j > iter_num; j--) {
            if (arr[j - 1] > arr[j]){
                int tmp_int = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp_int;
            }
        }
        iter_num++;
    }
    return arr;
}

void gen_unsorted(int* arr, int size, double deg) {
    for(int i = 0; i < size; i++) 
        arr[i] = rand() % 100000;
    
    sort2_sh(arr, size);

    int swap_num = deg * size;
    if (swap_num <= 0) swap_num = 1; 

    for(int j = 0; j < swap_num; j++) {
        int cell_1 = rand() % size;
        int cell_2 = rand() % size;
        
        int tmp = arr[cell_1];
        arr[cell_1] = arr[cell_2];
        arr[cell_2] = tmp;
    }
}

void generate_array(int* arr, int n, int max_val) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % max_val;
}

void gen_arr_digited(int* arr, int n, int digits) {
    if (digits < 1) {
        printf("Количество разрядов должно быть >= 1 \n");
        return;
    }

    int min_val = my_pow(10, digits - 1);
    int max_val = my_pow(10, digits) - 1;

    if (digits == 1) {
        min_val = 0;
        max_val = 9;
    }

    for (int i = 0; i < n; i++) 
        arr[i] = min_val + rand() % (max_val - min_val + 1);
}

int write_arr_to_file(const char* filename, const int* arr, int n) {
    if (filename == NULL || arr == NULL || n <= 0) {
        printf("wrong params\n");
        return -1;
    }

    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Ошибка открытия файла");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        if (fprintf(file, "%d ", arr[i]) < 0) {
            printf("Ошибка записи в файл \n");
            fclose(file);
            return -1;
        }
    }
    fprintf(file, "\n");
    
    if (fclose(file)) {
        printf("Ошибка закрытия файла");
        return -1;
    }

    return 0;
}

void write_arrs(const char* filename1, const char* filename2, const char* filename3) {
    srand(time(NULL)); 

    int size = 10;
    int max_size = 100000;
    int* arr = (int*)malloc(sizeof(int) * max_size);

    FILE* file1 = fopen(filename1, "w");
    if (file1) 
    {
        while (size <= max_size) 
        {
            fprintf(file1, "%d ", size);
            generate_array(arr, size, 100000);

            for (int i = 0; i < size; i++) 
                fprintf(file1, "%d ", arr[i]);
            fprintf(file1, "\n");

            size *= 10;
        }
        fclose(file1);
    }

    size = 10000;
    FILE* file2 = fopen(filename2, "w");
    if (file2) 
    {
        for (int i = 1; i <= 9; i++) 
        {
            double deg = 0.1 * i;

            fprintf(file2, "%d ", (int)(deg * 100));
            gen_unsorted(arr, size, deg);

            for (int j = 0; j < size; j++) 
                fprintf(file2, "%d ", arr[j]);
            fprintf(file2, "\n");
        }
        fclose(file2);
    }

    FILE* file3 = fopen(filename3, "w");
    if (file3) 
    {
        size = 1000;
        for (int digits = 1; digits <= 5; digits++) 
        {
            fprintf(file3, "%d ", digits);
            gen_arr_digited(arr, size, digits);

            for (int j = 0; j < size; j++) 
                fprintf(file3, "%d ", arr[j]);
            fprintf(file3, "\n");
        }
        fclose(file3);
    }

    free(arr);
}

int main() {
    write_arrs("text_data/input_size.txt", "text_data/input_unsort.txt", "text_data/input_radix.txt");
    return 0;
}