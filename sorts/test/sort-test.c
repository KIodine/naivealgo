#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "sorts.h"

/*
    An naive test framework for sorting algorithms with dataset:
    - Integer(C99 int on x86_64(linux 5.4), arch: Xeon-E3 1230v3)
    - Randomly distributed
*/

#define ARR_MEMBERS(arr) sizeof((arr))/sizeof(arr[0])

#define NL "\n"


static const int n_elems = 16000; // Tweak this value for test.

static 
int assert_ascending(int *arr, size_t n){
    for (size_t i = 0; i < n-1; i++){
        if (arr[i] > arr[i+1]){
            printf("Assertion violated: [%ld]=%d > [%ld]=%d"NL,
                i, arr[i], i+1, arr[i+1]);
            return -1;
        }
    }
    return 0;
}

static
int int_cmp(const void *a, const void *b){
    int x = *(int*)a, y = *(int*)b;
    return x > y;
}

// The baseline of all sorting algorithm.
static
void qsort_wrap(int *arr, size_t n){
    return qsort(arr, n, sizeof(int), int_cmp);
}


#define NAMED(symbol) {.sort_f=(symbol),.algo_name=#symbol}
struct {
    sorter_t sort_f;
    char *algo_name;
} sortss[] = {
    NAMED(qsort_wrap), // glibc qsort as baseline.
    NAMED(bubble),
    NAMED(selection),
    NAMED(insertion),
    NAMED(heapsort),
    NAMED(heapsort_canon),
    /*
    */
    NAMED(mergesort),
};
#undef NAMED


// Test each sort in `sorts`.
void test_sort(void){
    sorter_t sort_f;
    char const *name;
    struct timespec t0, dt;
    double us;
    int *shuffled_arr, *subj_arr;
    int res;

    /* Init a shuffled array, then copy it. */
    shuffled_arr = malloc(sizeof(int)*n_elems);
    for (int i = 0; i < n_elems; i++){
        shuffled_arr[i] = i;
    }
    shuffle(shuffled_arr, n_elems);
    subj_arr = malloc(sizeof(int)*n_elems);

    printf("Testing sort on array of %d integers."NL, n_elems);

    for (size_t i = 0; i < ARR_MEMBERS(sortss); i++){
        sort_f = sortss[i].sort_f;
        name = sortss[i].algo_name;
        // Dup shuffled array to subject.
        memcpy(subj_arr, shuffled_arr, sizeof(int)*n_elems);
        printf("Test sorting algorithm: %s...", name);
        
        clock_gettime(CLOCK_MONOTONIC, &t0);
        sort_f(subj_arr, n_elems);
        clock_gettime(CLOCK_MONOTONIC, &dt);
        res = assert_ascending(subj_arr, n_elems);
        if (res != 0){
            printf("Assertion violated on `%s`: array not in ascending order!"NL, name);
            abort();
        }
        
        if (dt.tv_nsec < t0.tv_nsec){
            dt.tv_nsec += 1000000000;
            dt.tv_sec -= 1;
        }
        dt.tv_sec -= t0.tv_sec;
        dt.tv_nsec -= t0.tv_nsec;
        us = ((double)dt.tv_sec)*1e6 + ((double)dt.tv_nsec)/1e3;
        us /= (double)n_elems;
        printf("avg time: %.3lf us/element"NL, us);
    }

    free(shuffled_arr);
    free(subj_arr);

    return;
}

int main(void){
    setbuf(stdout, NULL);
    test_sort();
    return 0;
}