#include "sorts.h"
#include "routines.h"

/*  Selection sort:
    It's like insertion sort, but does not swap numbers frequently,
    instead, it chooses the min/max value from the "rest" of list,
    and inserts into the sorted part, which in practice performs swap
    with the currently iterated element in the list.
    Though it has the same complexity (O(n^2)) as insertion sort, but
    it only preforms **one** swap during the inner loop, make it faster
    than insertion sort in practice.
    Selection sort may lost some attributes such as stability, compare
    to insertion sort. */

// Selection sort, in ascending order.
void selection(int *arr, size_t n){
    size_t i, j, min_idx;
    for (i = 0; i < n; i++){
        min_idx = i;
        for (j = i; j < n; j++){
            if (arr[j] < arr[min_idx]){
                min_idx = j;
            }
        }
        byte_swap(&arr[i], &arr[min_idx], sizeof(int));
    }
    return;
}
