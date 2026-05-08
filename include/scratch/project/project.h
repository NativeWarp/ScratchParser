#pragma once

#include "./metadata/metadata.h"
#include "./monitor/monitor.h"
#include "./target/target.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef int16_t Project_ExtensionsBitset;
enum {
    ExtensionsBitset_Pen                        = 1<<0,
    ExtensionsBitset_LEGOWeDo2                  = 1<<1,
    ExtensionsBitset_Music                      = 1<<2,
    ExtensionsBitset_MicroBit                   = 1<<3,
    ExtensionsBitset_TextToSpeech               = 1<<4,
    ExtensionsBitset_Translate                  = 1<<5,
    ExtensionsBitset_VideoSensing               = 1<<6,
    ExtensionsBitset_LEGOEV3                    = 1<<7,
    ExtensionsBitset_MakeyMakey                 = 1<<8,
    ExtensionsBitset_LEGOBoost                  = 1<<9,
    ExtensionsBitset_GoDirectForceAcceleration  = 1<<10
};

typedef struct Scratch_Project {
    size_t num_targets;    
    Project_Target* targets;

    size_t num_monitors;
    Project_Monitor* monitors;

    Project_ExtensionsBitset extensions; 
     
    Project_Metadata metadata;
} Scratch_Project;