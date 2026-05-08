#pragma once

#include "./target/asset/asset.h"
#include "./target/block/block.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum Monitor_DisplayMode {
    DisplayMode_Default,
    DisplayMode_Large,
    DisplayMode_Slider,
    DisplayMode_List
} Monitor_DisplayMode;

typedef enum Monitor_MonitorType {
    MonitorType_Variable,
    MonitorType_List
} Monitor_MonitorType;

// A Variable Watcher (or Monitor) on the Stage.
typedef struct Project_Monitor {
    const char* id; // Internal ID.

    Monitor_DisplayMode display_mode;
    Block_OpCode opcode;

    const char* monitor_name; 
    Monitor_MonitorType monitor_type;

    Target_Asset* target; // Optional. Target associated with the Monitor.

    // TODO - what are values?
    const char* value;

    int64_t width;
    int64_t height;

    int64_t x;
    int64_t y;

    int64_t slider_minimum;
    int64_t slider_maximum;

    bool is_visible;
    bool is_discrete; // Whether the slider only allows integer values.
} Project_Monitor;