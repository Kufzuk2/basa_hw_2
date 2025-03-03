#include <stdio.h>
#include <time.h>
#include <stdlib.h>



enum sort_opt {
    sort_2    = 1,
    sort_2_sh = 2,
    sort_comb = 3
};



int check_if_sorted(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1])
            return 0;
    }
    return 1;

}


void print_arr(int* arr, int size) {
    for(int i = 0; i < size; i++) 
        printf("%d ", arr[i]);
    printf("\n");
    printf("\n");
}



int* sort2(int* arr, int size){
    if (!arr){
        printf("empty arr \n");
        return NULL;
    }

    if (check_if_sorted(arr, size))
        return arr;

    int cur_size = size;
    int tmp_int  = 0;

    while (cur_size) { //???

        for (int i = 0; i < cur_size - 1; i++) {
            if (arr[i] > arr[i + 1]){

                tmp_int    = arr[i + 1];
                arr[i + 1] = arr[i    ];
                arr[i    ] =    tmp_int;
            }    
        }
        cur_size--;
    }
    return arr;

}

int* sort2_sh(int* arr, int size){
    if (!arr){
        printf("empty arr \n");
        return NULL;
    }

    if (check_if_sorted(arr, size)) {
        printf("already sorted arr \n");
        return arr;
    }

    int cur_size   =  size;
    int tmp_int    =  0;
    int iter_num = 0;

    while (cur_size) { //???

        for (int i = iter_num; i < size - iter_num - 1; i++) {

            if (arr[i] > arr[i + 1]){

                tmp_int    = arr[i + 1];
                arr[i + 1] = arr[i    ];
                arr[i    ] =    tmp_int;
            }    
        }
        
    //    cur_size--;
        //printf("cur_size = %d \n", cur_size);
      //  print_arr(arr, size);
  /*      if (cur_size < 2)
            return arr; // not sure
*/

        for (int j = size - iter_num - 1; j > iter_num; j--) {
            if (arr[j - 1] > arr[j]){
                tmp_int    = arr[j - 1];
                arr[j - 1] = arr[j    ];
                arr[j    ] =    tmp_int;

            }
        }
    //    cur_size--;
        //printf("cur_size = %d \n", cur_size);
        //print_arr(arr, size);
  /*      if (cur_size < 2)
            return arr; // not sure
*/
        iter_num++;

        if (iter_num * 2 >= size)
            return arr;
    }
    return arr;

}

int* comb_sort (int* arr, int size) {
    if (!arr){
        printf("empty arr \n");
        return NULL;
    }

    if (check_if_sorted(arr, size)) {
        printf("already sorted arr \n");
        return arr;
    }

    int tmp_int    =   0;
    int gap = size / 1.3;
    
    while (gap > 1) {
        int i = 0;
        while(i + gap < size) {
            if (arr[i] > arr[i + gap]){

                tmp_int      = arr[i + gap];
                arr[i + gap] = arr[i      ];
                arr[i      ] =      tmp_int;
            }    
            i += gap;
        }
        //printf("i = %d, gap = %d \n", i, gap);
        gap = gap / 1.3;
        //printf("i = %d, gap = %d \n", i, gap);
    }

    return sort2_sh(arr, size);
}


void make_test(int arr_size, int sort_type) {
    int size = arr_size;
    int arr[size];
    

    for(int i = 0; i < arr_size; i++) 
        arr[i] = rand() % 1000;

    printf("initial \n");
    print_arr(arr, size);

    clock_t start, end;
    double used_time;

    start = clock(); 


    if (sort_type == 1)
        sort2     (arr, size);

    else if (sort_type == 2)
        sort2_sh  (arr, size);

    else if (sort_type == 3)
        comb_sort (arr, size);
    
    end = clock(); 

    used_time = ((double)(end - start)) / CLOCKS_PER_SEC; 
    
    printf("sorted \n");
    print_arr(arr, size);
    printf("Time taken: %f seconds\n", used_time);

    if (check_if_sorted(arr, size)) {
        printf("!TEST PASSED! \n");
    }
    else
        printf("!*!*!*!*TEST FAILED!*!*!*!*\n");

    printf("\n");
    printf("\n");   
}

int* cp_arr(int* arr, int* new_arr, int size) {
    if (!arr)
        return NULL;
    
    for(int i = 0; i < size; i++) 
        new_arr[i] = arr[i];

    return new_arr;
}


void time_cmp_test () {
    int size     =      10;
    int max_size = 1000000;

    int* arr = (int*) malloc(sizeof(int) * max_size);

    while (size <= max_size) {
        for(int i = 0; i < size; i++) 
            arr[i] = rand() % 100000;

        print_time_deps(arr, size, 1);
        size *= 10;
    }

    free(arr);

}


void print_time_deps(int arr, int size, double unsort_deg) {

    clock_t start, end;

    double used_time1;
    double used_time2;
    double used_time3;

    int* arr2 = (int*) malloc(sizeof(int) * size);
    int* arr3 = (int*) malloc(sizeof(int) * size);


    start = clock();
    sort2(arr, size);
    end   = clock();
    used_time1 = ((double)(end - start)) / CLOCKS_PER_SEC; 

    start = clock();
    sort2_sh(arr2, size);
    end   = clock();
    used_time2 = ((double)(end - start)) / CLOCKS_PER_SEC; 

    start = clock();
    comb_sort(arr3, size);
    end   = clock();
    used_time3 = ((double)(end - start)) / CLOCKS_PER_SEC; 

    printf("size = %d, unsort_deg = %f, sort2 time = %f, shaker sort time = %f, comb_sort time = %f \n", 
            size, unsort_deg, used_time1, used_time2, used_time3);

    free(arr2);
    free(arr3);
}


void gen_unsorted(int* arr, int size, double deg) {
    for(int i = 0; i < size; i++) 
        arr[i] = rand() % 1000;
    sort2_sh(arr, size);
    // now arr is sorted

    int swap_num = size * deg;
    
    int cell_1 = 0;
    int cell_2 = 0;
    int tmp    = 0;

    for(int j = 0; j < size; j += 2){
        cell_1 = rand() % size;
        cell_2 = rand() % size;

        tmp         = arr[cell_1];
        arr[cell_1] = arr[cell_2];
        arr[cell_2] =         tmp;
    } 
}


void test_sorted_degree(int size) {
    int* arr = (int*) malloc(sizeof(int) * size);

    double  deg =   0.1;

    for (int i = 0; i < 9; i++) {
        gen_unsorted   (arr, size, deg);
        print_time_deps(arr, size, deg);

        deg += i / 10;
    }

    free(arr);
}

int main() {
    srand(time(NULL));
/*
    int test_num = 5;
    //int size = rand() % 10;
    int size = 122;

    for (int i = 0; i < test_num; i++) {
        make_test(size, sort_2);
    }
*/

    time_cmp_test();

 /*  for (int i = 0; i < test_num; i++) {
    make_test(size, 2);
}*/
}