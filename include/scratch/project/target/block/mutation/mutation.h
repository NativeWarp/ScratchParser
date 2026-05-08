#pragma once

#include "./argument/argument.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// A Custom Block in a Project.
typedef struct Block_Mutation {
    const char* block_name; // Formattable string of the block's name, including arguments.

    size_t num_arguments;
    Mutation_Argument* arguments; // Array of arguments.

    bool is_warp; // Whether the block should run without screen refresh.
} Block_Mutation;