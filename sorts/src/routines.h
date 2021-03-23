#pragma once

/*
    Internal-use only and inlining routines.
*/

#include <stddef.h>

/* Bytewise swapping, suggest inlining for speedup. */
static inline
void byte_swap(void *a, void *b, size_t sz){
    char tmp;
    char *__a = a, *__b = b;
    for (;sz-- > 0;){
        tmp = *__a;
        // post increment for saving few characters :)
        *__a++ = *__b;
        *__b++ = tmp;
    }
    return;
}
