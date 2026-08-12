#pragma once

#include <stddef.h>
#include <sys/cdefs.h>

void *nullable mem_alloc (size_t __size) __THROW __attribute_malloc__
     __attribute_alloc_size__ ((1)) __wur;

void *nullable mem_calloc (size_t __nmemb, size_t __size)
     __THROW __attribute_malloc__ __attribute_alloc_size__ ((1, 2)) __wur;

void *nullable mem_realloc (void *nullable __ptr, size_t __size)
     __THROW __attribute_warn_unused_result__ __attribute_alloc_size__ ((2));

void mem_dealloc (void *nullable __ptr) __THROW;
