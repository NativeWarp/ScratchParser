#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Target_Variable {
    const char* id; // Internal ID.
    const char* name;

    // TODO - what are values?
    const char* value;
    bool is_cloud;
} Target_Variable;