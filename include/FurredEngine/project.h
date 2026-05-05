#pragma once

#include <scratchparser_export.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const char* id; // Internal ID.

    const char* name;
    // TODO - what are values?
    int64_t value;
    bool is_cloud;
} Target_Variable;

typedef struct {
    const char* id; // Internal ID.

    const char* name;
    size_t num_elements;
    // TODO - what are values?
    int64_t* elements; // Array of list elements.
} Target_List;

typedef struct {
    const char* id; // Internal ID.
    
    const char* name;
} Target_Broadcast;

// TODO - finish this
typedef struct {
    const char* id; // Internal ID.
    
    const char* name;
} Target_Block;

// TODO - finish this
typedef struct {
    const char* id; // Internal ID.
    
    const char* name;
} Target_Comment;

// TODO - finish this
typedef struct {
    const char* id; // Internal ID.
    
    const char* name;
} Target_Costume;

// TODO - finish this
typedef struct {
    const char* id; // Internal ID.
    
    const char* name;
} Target_Sound;

typedef enum {
    Type_Sprite,
    Type_Stage
} Target_Type;

typedef enum {
    VideoState_On,
    VideoState_Off,
    VideoState_OnFlipped
} Target_VideoState;

typedef enum {
    TextToSpeechLanguage_Danish,
    TextToSpeechLanguage_Dutch,
    TextToSpeechLanguage_English,
    TextToSpeechLanguage_French,
    TextToSpeechLanguage_German,
    TextToSpeechLanguage_Icelandic,
    TextToSpeechLanguage_Italian,
    TextToSpeechLanguage_Polish,
    TextToSpeechLanguage_BrazillianPortuguese,
    TextToSpeechLanguage_EuropeanPortuguese,
    TextToSpeechLanguage_Russian,
    TextToSpeechLanguage_EuropeanSpanish,
    TextToSpeechLanguage_LatinAmericanSpanish,
    TextToSpeechLanguage_MandarinChinese,
    TextToSpeechLanguage_Korean,
    TextToSpeechLanguage_Norwegian,
    TextToSpeechLanguage_Romanian,
    TextToSpeechLanguage_Swedish,
    TextToSpeechLanguage_Turkish,
    TextToSpeechLanguage_Welsh

} Target_TextToSpeechLanguage;

typedef enum {
    RotationStyle_AllAround,
    RotationStyle_LeftRight,
    RotationStyle_DontRotate
} Target_RotationStyle;

// A Stage or Sprite.
typedef struct {
    Target_Type type;
    const char* name;

    size_t num_variables;
    Target_Variable* variables; // Array of variables.
    size_t num_lists;
    Target_List* lists; // Array of lists.
    size_t num_broadcasts;
    Target_Broadcast* broadcasts; // Array of broadcasts.
    size_t num_blocks;
    Target_Block* blocks; // Array of blocks.
    size_t num_comments;
    Target_Comment* comments; // Array of comments.
    size_t num_costumes;
    Target_Costume* costumes; // Array of costumes.
    size_t num_sounds;
    Target_Sound* sounds; // Array of sounds.

    int64_t current_costume; // Current costume index.
    int64_t current_layer; // Current layer index.

    float volume; // Current volume out of 100.

// Stage Properties

    float* stage_tempo; // Optional. Tempo in BPM.
    Target_VideoState* stage_video_state; // Optional.
    float* stage_video_transparency; // Optional.
    Target_TextToSpeechLanguage* stage_tts_language; // Optional.

// Sprite Properties

    bool* sprite_is_visible; // Optional.
    size_t* sprite_x; // Optional.
    size_t* sprite_y; // Optional.
    float* sprite_size; // Optional. Size out of 100.
    float* sprite_direction; // Optional.
    bool* sprite_is_draggable; // Optional.
    Target_RotationStyle* sprite_rotation_style; // Optional.
} Project_Target;

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

typedef struct {
    size_t num_targets;    
    Project_Target* targets;

    size_t num_monitors;
    Project_Monitor* monitors;

    Project_ExtensionsBitset extensions; 
     
    Project_Metadata metadata;
} Scratch_Project;