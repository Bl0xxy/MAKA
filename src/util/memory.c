#include "util/memory.h"
#include <stdlib.h>

void *nullable mem_alloc (size_t __size) {
    return malloc(__size);
}

void *nullable mem_calloc (size_t __nmemb, size_t __size) {
    return calloc(__nmemb, __size);
}

void *nullable mem_realloc (void *nullable __ptr, size_t __size) {
    return realloc(__ptr, __size);
}

void mem_dealloc (void *nullable __ptr) {
    return free(__ptr);
}
