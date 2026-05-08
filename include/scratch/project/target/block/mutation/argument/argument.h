#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// An Argument for a Custom Block
typedef struct Mutation_Argument {
    const char* id; // Internal ID.
    const char* name;
} Mutation_Argument;