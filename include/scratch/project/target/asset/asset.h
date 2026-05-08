#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum Asset_Format {
    Format_Vector, // .svg
    Format_Bitmap // .png
} Asset_Format;

// A Costume or Sound in a Target
typedef struct Target_Asset {
    const char* name;

    const char* asset_id; // Asset file name.
    Asset_Format asset_format;

// Costume Properties
    int64_t scaling_factor; // Factor by which the costume should be scaled.
    int64_t rotation_center_x;
    int64_t rotation_center_y;

// Sound Properties
    uint64_t sampling_rate;
    uint64_t sample_count;
} Target_Asset;