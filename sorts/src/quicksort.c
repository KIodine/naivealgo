#include <assert.h>

#include "sorts.h"
#include "routines.h"
// TODO: Reference qsort in glibc.

/*  Quicksort:
    One of the sorting algorithms that utilizes "divide and conquer"
    strategy.
    The major step in qsort is "partitioning" -- dividing a list into
    two parts, seperated by a "pivot", elements in one side are gt
    pivot, the other side, lt. By doing so until the length of partition
    equals to one or small enough for other sorting algorithms, then
    quicksort is completed. */

/*  References:
    https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto
*/


// Partition algorithm using lomuto's algo, returns the index where
// pivot at in the end.
static inline size_t
lomuto_partition(int *arr, size_t pivot_idx, size_t n){
    // i: The candidate index of swapping.
    // j: Index currently being inspected.
    size_t i = 0, j = 0;
    // move
    byte_swap(&arr[pivot_idx], &arr[n-1], sizeof(int));
    pivot_idx = n-1;
    for (;j < pivot_idx; j++){
        if (arr[j] < arr[pivot_idx]){
            // Avoid swap with self.
            if (i != j){
                byte_swap(&arr[i], &arr[j], sizeof(int));
            }
            i++;
        }
    }
    byte_swap(&arr[i], &arr[j], sizeof(int));
    // At this point, `j` should points to the tail of list.
    assert(j == (n-1));
    return i;
}

static inline 
size_t hoare_partition(int arr[], size_t pivot_idx, size_t n){
    size_t lo = 0, hi = n - 1;
    int mid = arr[pivot_idx];

    for (;;){
        for (;arr[lo] < mid;){
            lo += 1;
        }
        for (;mid < arr[hi];){
            hi -= 1;
        }
        if (lo >= hi){
            break;
        }
        if (lo < hi){
            byte_swap(&arr[lo], &arr[hi], sizeof(int));
            lo += 1;
            hi -= 1;
        }
    }
    return lo < hi? lo: hi;
}

/* Quicksort using recursive method, sorting list in ascending order. */
void quicksort_recur(int *arr, size_t n){
    // Simply choose the middle of list as pivot.
    size_t pivot = (n >> 1) - 1;

    // Avoid small `n` causes `pivot` underflows.
    if (n <= 1){
        return;
    }

    //pivot = lomuto_partition(arr, pivot, n);
    pivot = hoare_partition(arr, pivot, n);
    quicksort_recur(arr, pivot+1);
    quicksort_recur(&arr[pivot+1], n-(pivot+1));
    return;
}
