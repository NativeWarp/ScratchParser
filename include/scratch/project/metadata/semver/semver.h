#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Metadata_SemVer {
    int32_t major;
    int32_t minor;
    int32_t patch;
} Metadata_SemVer;