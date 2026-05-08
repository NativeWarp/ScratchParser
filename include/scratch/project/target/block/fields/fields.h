#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// A dropdown in a Block
typedef struct Block_Fields {
    const char* id; // Internal ID.

    // TODO - what are values?
    const char* value; // Field name.
    const char* reference; // Optional. Internal ID pointing to another Target
} Block_Fields;