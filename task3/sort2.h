#pragma once

enum sort_opt {
    sort_2    = 1,
    sort_2_sh = 2,
    sort_comb = 3
};

void print_time_deps   (int* arr,      int  size, double unsort_deg, FILE* output_file); 
void test_sorted_degree(               int  size,                    FILE* output_file); 
void time_cmp_test     (                                             FILE* output_file);

int* cp_arr            (int* arr,      int* new_arr,  int size                        );
void gen_unsorted      (int* arr,      int  size,     double deg                      ); 
void make_test         (int  arr_size, int  sort_type                                 );
                
int  check_if_sorted   (int* arr,      int  size                                      ); 
void print_arr         (int* arr,      int  size                                      ); 
int* sort2             (int* arr,      int  size                                      );
int* sort2_sh          (int* arr,      int  size                                      );
int* comb_sort         (int* arr,      int  size                                      );

