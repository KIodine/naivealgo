#include <stdlib.h>

#include "sorts.h"
#include "routines.h"


void byte_shuffle(void *arr, size_t n_elems, size_t sz){
    size_t rnd_idx;
    char *__arr = arr;
    for (size_t i = 0; i < n_elems; ++i){
        rnd_idx = rand() % n_elems;
        byte_swap(&__arr[i*sz], &__arr[rnd_idx*sz], sz);
    }
    return;
}

// for each element in array, swap with randomly chosen one.
void shuffle(int *arr, size_t n){
    int rnd_idx;
    for (size_t i = 0; i < n; i++){
        rnd_idx = rand() % n;
        byte_swap(&arr[i], &arr[rnd_idx], sizeof(int));
    }
    return;
}
