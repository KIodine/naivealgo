#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "sorts.h"
#include "routines.h"

/*  Mergesort(recursive): 
    Mergesort divides the entire array into smaller subarrays, and so
    on, until it is small enough to process.
    After dividing all the subarrays, the merge process begins,
    merging sorted subarrays into a larger subarray, until
    all subarray are merged into the original array. */

/*  Mergesort does highly utilizes cache through intense momory access
    in a small region (maybe 3 separte but small continuous region), 
    but in exchange of a lot memory footprint (O(n)) and relys on
    `malloc` call to get auxilliary space, and yet being generalized. */

/* Sorting list in ascending order with mergesort algorithm. */
void mergesort(int *arr, size_t n){
    // Handle root case.
    if (n == 1){
        return;
    }
    if (n == 2){
        if (arr[0] > arr[1]){
            byte_swap(&arr[0], &arr[1], sizeof(int));
        }
        return;
    }
    // Do divide and merge.
    size_t b_base = n >> 1;
    // Divide.
    mergesort(arr, b_base);
    mergesort(&arr[b_base], n-b_base);
    
    // Merge, merging two subarrays to an aux array and copy back.
    int *aux = malloc(sizeof(int)*n); // or static space.
    // NOTE: Initialize `mv_idx`, though it's not necessary.
    size_t a_idx = 0, b_idx = b_base, mv_idx = 0, dst_idx = 0;
    for (;;){
        // Ensure indexes are bounded and if the other index is reached
        // its end, short circuit to the opposite.
        if (a_idx < b_base && (b_idx >= n || arr[a_idx] < arr[b_idx])){
            mv_idx = a_idx; a_idx++;
        } else if (b_idx < n && (a_idx >= b_base || arr[b_idx] < arr[a_idx])){
            mv_idx = b_idx; b_idx++;
        }
        aux[dst_idx] = arr[mv_idx];
        dst_idx += 1;
        if (a_idx >= b_base && b_idx >= n){
            // both subarray are consumed.
            assert(dst_idx == n);
            break;
        }
    }
    // copy back;
    memcpy(arr, aux, sizeof(int)*n);    // from `string.h`.
    free(aux);

    return;
}
