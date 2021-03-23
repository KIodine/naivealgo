#include "sorts.h"
#include "routines.h"

/* One of the most naive sorting algorithm, for each element in
   arr, if the latter element is gt/lt the current element, do
   swap them. */

// Bubble sort, in ascending order.
void bubble(int *arr, size_t n){
    for (size_t i = 0; i < n; i++){
        for (size_t j = i+1; j < n; j++){
            if (arr[i] > arr[j]){
                byte_swap(&arr[i], &arr[j], sizeof(int));
            }
        }
    }
    return;
}
