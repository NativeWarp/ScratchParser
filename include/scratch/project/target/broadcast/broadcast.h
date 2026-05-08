#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Target_Broadcast {
    const char* id; // Internal ID.
    const char* name;
} Target_Broadcast;