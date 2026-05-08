#pragma once

#include "./semver/semver.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Project_Metadata {
    Metadata_SemVer editor_version;
    Metadata_SemVer vm_version;

    const char* user_agent;
} Project_Metadata;