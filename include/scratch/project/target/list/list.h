#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Target_List {
    const char* id; // Internal ID.
    const char* name;
    
    size_t num_elements;
    // TODO - what are values?
    const char** values; // Array of list elements.
} Target_List;