#include <assert.h>

#include "sorts.h"
#include "routines.h"

/*  Heapsort:
    Like selection sort but utilizing heap data structure.
    Usually using binary heap, heapsort "chooses" the minimum
    element from heap and swap with the last element in the list
    then shirinks the size of list.
    Though has O(nlogn) complexity, unable to utilizing cache and 
    more swaps make it slower than some O(n^2) sort(selection sort)
    on real machine. */

static void sift_down(int *arr, size_t idx, size_t n){
    size_t swp, left, right;
    for (;;){
        swp = 0; // init/reset swp.
        idx += 1;
        // Q: just shift index?
        left = (idx << 1);
        right = (left + 1);
        assert(left > idx && right > idx);
        if (left <= n && arr[idx-1] > arr[left-1]){
            swp = left;
        }
        if (right <= n && arr[idx-1] > arr[right-1] && arr[right-1] < arr[left-1]){
            swp = right;
        }
        if (swp == 0){
            break;
        }
        idx -= 1; swp -= 1; // convert back to normal index.
        byte_swap(&arr[idx], &arr[swp], sizeof(int));
        assert(swp > idx);
        idx = swp; // proceed down the heap.
    }
    return;
}

static void min_heapify(int *arr, size_t n){
    // FIXME: Handle case n = 1.
    if (n <= 1){
        return;
    }
    // Iterate backward.
    for (size_t i = (n>>1)-1;; i--){
        sift_down(arr, i, n);
        if (i == 0){
            break;
        }
    }
    return;
}

/*  slightly different implementation, instead of using maxheap and 
    swap with the last element with the first, "moving" the base
    of "heap" after each min heapify operation.
    > This version is about 2x slower compare to canonical implementation
    of heapsort, the guess now is less utilization of cache due to
    the "moving heap" part. */

// Sort list in ascending order using heapsort algorithm.
void heapsort(int *arr, size_t n){
    for (size_t i = 0; i < n; i++){
        // Move the heap one element further.
        min_heapify(&arr[i], n-i);
    }
    return;
}

// --- Canonical heapsort, using max heapify and end swapping ---
static
void sift_down_max(int *arr, size_t idx, size_t n){
    size_t swp, left, right;
    for (;;){
        swp = 0; // init/reset swp.
        idx += 1;
        // Q: just shift index?
        left = (idx << 1);
        right = (left + 1);
        assert(left > idx && right > idx);
        if (left <= n && arr[idx-1] < arr[left-1]){
            swp = left;
        }
        if (right <= n && arr[idx-1] < arr[right-1] && arr[right-1] > arr[left-1]){
            swp = right;
        }
        if (swp == 0){
            break;
        }
        idx -= 1; swp -= 1; // convert back to normal index.
        byte_swap(&arr[idx], &arr[swp], sizeof(int));
        assert(swp > idx);
        idx = swp; // proceed down the heap.
    }
    return;
}

static
void max_heapify(int *arr, size_t n){
    if (n <= 1){
        return;
    }
    for (size_t i = (n>>1)-1;;i--){
        sift_down_max(arr, i, n);
        if (i == 0){break;}
    }
    return;
}

// Canonical heapsort, sorting list in ascending order.
void heapsort_canon(int *arr, size_t n){
    for (size_t i = 0; i < n; i++){
        max_heapify(arr, n-i);
        // do swap with last and "shrink" list size.
        byte_swap(&arr[0], &arr[(n-i)-1], sizeof(int));
    }
    return;
}