#include <stdio.h>
#include <time.h>
#include <stdlib.h>






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


int* cp_arr(int* arr, int* new_arr, int size) {
    if (!arr)
        return NULL;
    
    for(int i = 0; i < size; i++) 
        new_arr[i] = arr[i];

    return new_arr;
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
        //printf("already sorted arr \n");
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
        
        for (int j = size - iter_num - 1; j > iter_num; j--) {
            if (arr[j - 1] > arr[j]){
                tmp_int    = arr[j - 1];
                arr[j - 1] = arr[j    ];
                arr[j    ] =    tmp_int;

            }
        }
        iter_num++;

        if (iter_num * 2 >= size)
            return arr;
    }
    return arr;

}

int* comb_sort (int* arr, int size) {
     	int        tmp;
        int          k;
        int gap = size;

        long long cnt=0;

        while(size > 1) {
            gap /= 1.247f;
                  
            if (gap < 1) 
                gap = 1; 

            k = 0;

            for (int i = 0; i + gap < size; i++) { 
                if(arr[i] > arr[i +  gap]) {
                    tmp    = arr[i      ];
                    arr[i] = arr[i + gap];
                    arr[i + gap]   =  tmp; 	
                    k = i;
                }
                cnt++;
            }
            if (gap == 1) 
                size = k + 1; 
        }
    }



void print_time_deps(int* arr, int size, double unsort_deg, FILE* output_file) {

    clock_t start, end;

    double used_time1;
    double used_time2;
    double used_time3;

    int* arr2 = (int*) malloc(sizeof(int) * size);
    int* arr3 = (int*) malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++){
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }


    start = clock();
    sort2(arr, size);
    end   = clock();
    used_time1 = ((double)(end - start)) / CLOCKS_PER_SEC; 

    if (check_if_sorted(arr, size)) {
        printf("sort2 OK \n");
    }


    start = clock();
    sort2_sh(arr2, size);
    end   = clock();
    used_time2 = ((double)(end - start)) / CLOCKS_PER_SEC; 

    if (check_if_sorted(arr2, size)) {
        printf("sort2_sh OK \n");
    }


    start = clock();
    comb_sort(arr3, size);
    end   = clock();
    used_time3 = ((double)(end - start)) / CLOCKS_PER_SEC; 

    if (check_if_sorted(arr3, size)) {
        printf("comb sort OK \n");
    }



    printf("size = %d, unsort_deg = %f, sort2 time = %f, shaker sort time = %f, comb_sort time = %f \n", 
            size, unsort_deg, used_time1, used_time2, used_time3);

    fprintf(output_file, "%d %f %f %f %f\n", size, unsort_deg * 100, used_time1, used_time2, used_time3);



    free(arr2);
    free(arr3);
}


void gen_unsorted(int* arr, int size, double deg) {
    for(int i = 0; i < size; i++) 
        arr[i] = rand() % 100000;
    sort2_sh(arr, size);
    // now arr is sorted

    int  swap_num  =                         deg * size ;
    int* arr_copy  =   (int*) malloc(sizeof(int) * size);

    arr_copy       =         cp_arr(arr, arr_copy, size);
    int cell_1 = rand() % size;
    int cell_2 = rand() % size;

    int tmp = 0;

    for(int j = 0; j < swap_num; j += 2){
        cell_1 = rand() % size;
        cell_2 = rand() % size;

        if (((arr[cell_1] != arr_copy[cell_1]) || (arr[cell_2] != arr_copy[cell_2]))) {
            j -= 2;
            continue;
        }

        tmp         = arr[cell_1];
        arr[cell_1] = arr[cell_2];
        arr[cell_2] =         tmp;

        

    } 
    free(arr_copy);
}



void make_test(int arr_size, int sort_type) {
    int size = arr_size;
    int* arr = (int*) malloc(sizeof(int) * arr_size);


    for(int i = 0; i < arr_size; i++) 
        arr[i] = rand() % 1000;

  //  printf("initial \n");
//    print_arr(arr, size);

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
    
    //printf("sorted \n");
    //print_arr(arr, size);
    printf("Time taken: %f seconds\n", used_time);

    if (check_if_sorted(arr, size)) {
        printf("!TEST PASSED! \n");
    }
    else
        printf("!*!*!*!*TEST FAILED!*!*!*!*\n");

    printf("\n");
    printf("\n");   
    free(arr);
}

void time_cmp_test (FILE* output_file) {
    int size     =     10;
    int max_size = 100000;

    int* arr = (int*) malloc(sizeof(int) * max_size);

    while (size <= max_size) {
        for(int i = 0; i < size; i++) 
            arr[i] = rand() % 100000;

        print_time_deps(arr, size, 1.0, output_file);
        size *= 10;
    }

    free(arr);

}



void test_sorted_degree(int size, FILE* output_file) {
    int* arr = (int*) malloc(sizeof(int) * size);

    double  deg =   0.1;

    for (int i = 0; i < 9; i++) {
        deg = 0.1 * (i + 1);
        gen_unsorted   (arr, size, deg);
        print_time_deps(arr, size, deg, output_file);
        
        
    }

    free(arr);
}

