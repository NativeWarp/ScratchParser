#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum Input_Type {
    Type_ImmediateValue,
    Type_Reference
} Input_Type;

// An Input in a Block
typedef struct Block_Input {
    const char* id; // Internal ID.
    Input_Type type;

    // TODO - what are values?
    const char* value; // Immediate value, or internal ID pointing to another Target.
} Block_Input;