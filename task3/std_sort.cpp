#include "radix_sort.h"
#include <algorithm>

extern "C" {
    void std_sort_wrapper(int* arr, int n) {
        std::sort(arr, arr + n);
    }
}