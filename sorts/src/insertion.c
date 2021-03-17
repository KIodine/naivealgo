#include "sorts.h"
#include "routines.h"

/*  Insertion sort.
    For each element in a list, swap "backward" until it is no longer
    gt/lt its "predecessor". The procedure described above is one of
    the way insertion sort works, but the "for each" can also be
    interperted as "when a number is 'appended' to the list", thus
    insertion sort can also be an "online" sorting algorithm.
    Other advantages include:
    - In-place
    - Stable
    - Simplicity(though complexity is O(n^2))
    */

// Insertion sort, in ascending order.
void insertion(int *arr, size_t n){
    size_t i, j;
    for (i = 0; i < n; i++){
        // goes backward.
        for (j = (n-1); j > i; j--){
            if (arr[j-1] > arr[j]){
                byte_swap(&arr[j-1], &arr[j], sizeof(int));
            }
        }
    }
    return;
}
