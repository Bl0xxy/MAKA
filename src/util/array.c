#include "util/memory.h"

void array_reserve_impl(
    void *nullable *nonnull data,
    size_t *nonnull capacity,
    size_t element_size,
    size_t new_capacity
) {
    if (new_capacity <= *capacity)
        return;

    auto new_data = mem_realloc(*data, new_capacity * element_size);

    if (new_data == nullptr)
        return;

    *data = new_data;
    *capacity = new_capacity;
}
