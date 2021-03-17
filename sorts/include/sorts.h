#ifndef SORTS_H
#define SORTS_H

#include <stddef.h>
/*
    A naive practice of sorting algorithms, currently includes:
    - bubble sort
    - insertion sort
    - merge sort
    - quick sort

    Targets on integer sorting, but may easily adapt to any type of data.
*/

typedef void (*sorter_t)(int *, size_t);


void shuffle(int *arr, size_t n);

// Uncomment symbol on complete.
void bubble(int *arr, size_t n);
void selection(int *arr, size_t n);
void insertion(int *arr, size_t n);
//void merge(int *arr, size_t n);
// Avoid redefining `qsort` in <stdlib.h>.
// TODO: write a not so obscured version of glibc qsort.
//void quicksort(int *arr, size_t n);


#endif