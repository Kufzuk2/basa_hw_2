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


int* sort2(int* arr, int size){
    if (!arr){
        printf("empty arr \n");
        return NULL;
    }

    if (check_if_sorted(arr, size))
        return arr;

    int cur_end  = 2147483649; //2**31 - 1 
    int cur_size = size;
    int tmp_int  = 0;

    while (cur_end != arr[0]) { //???

        for (int i = 0; i < cur_size - 1; i++) {
            if (arr[i] > arr[i + 1]){

                tmp_int    = arr[i + 1];
                arr[i + 1] = arr[i    ];
                arr[i    ] =    tmp_int;
            }    
        }
        cur_end = arr[cur_size - 1];
        cur_size--;
    }
    return arr;

}


void make_test(int arr_size) {
    int size = arr_size;
    int arr[size];
//    srand(time(NULL));
    

    for(int i = 0; i < 8; i++) 
        arr[i] = rand() % 1000;

    printf("initial \n");
        for(int i = 0; i < size; i++) 
        printf("%d ", arr[i]);
    printf("\n");

    sort2(arr, size);

    printf("sorted \n");
    for(int i = 0; i < size; i++) 
        printf("%d ", arr[i]);
    printf("\n");
    printf("\n");

}

int main() {
    srand(time(NULL));
    int size;
    int test_num = 10;

    for (int i = 0; i < test_num; i++) {
        size = rand() % 10;
        make_test(size);
    }

}