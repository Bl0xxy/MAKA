#pragma once

#include <stddef.h>
#include <assert.h>
#include "util/memory.h"

#define array(T) \
    struct { \
        T *nullable data; \
        size_t length; \
        size_t capacity; \
    }

#define array_reserve(__self, __new_capacity) \
    array_reserve_impl( \
        (void **)&(__self)->data, \
        &(__self)->capacity, \
        sizeof(*(__self)->data), \
        (__new_capacity) \
    )

#define array_push(__self, __value) \
    do { \
        if ((__self)->length == (__self)->capacity) \
            array_reserve((__self), (__self)->capacity ? (__self)->capacity * 2 : 8); \
        (__self)->data[(__self)->length++] = (__value); \
    } while (0)

#define array_pop(__self) \
    (assert((__self)->length > 0), \
        (__self)->data[--(__self)->length])

#define array_clear(__self) \
    ((__self)->length = 0)

#define array_free(__self) \
    do { \
        mem_dealloc((__self)->data); \
        (__self)->data = nullptr; \
        (__self)->length = 0; \
        (__self)->capacity = 0; \
    } while (0)

void array_reserve_impl(
    void *nullable *nonnull data,
    size_t *nonnull capacity,
    size_t element_size,
    size_t new_capacity
);
