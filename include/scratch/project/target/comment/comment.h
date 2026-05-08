#pragma once

#include "../block/block.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Target_Comment {
    Target_Block* attached_block; // Block the comment is attached to

    int64_t x;
    int64_t y;
    int64_t width;
    int64_t height;

    bool is_minimized;

    const char* text; // Contents of the comment
} Target_Comment;