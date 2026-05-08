#pragma once

#include "./asset/asset.h"
#include "./block/block.h"
#include "./comment/comment.h"
#include "./broadcast/broadcast.h"
#include "./list/list.h"
#include "./variable/variable.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum Target_Type {
    Type_Sprite,
    Type_Stage
} Target_Type;

typedef enum Target_VideoState {
    VideoState_On,
    VideoState_Off,
    VideoState_OnFlipped
} Target_VideoState;

typedef enum Target_TTSLanguage {
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
} Target_TTSLanguage;

typedef enum Target_RotationStyle {
    RotationStyle_AllAround,
    RotationStyle_LeftRight,
    RotationStyle_DontRotate
} Target_RotationStyle;

// A Stage or Sprite in the Project.
typedef struct Project_Target {
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
    Target_Asset* costumes; // Array of costumes.
    size_t num_sounds;
    Target_Asset* sounds; // Array of sounds.

    int64_t current_costume; // Current costume index.
    int64_t current_layer; // Current layer index.

    float volume; // Current volume out of 100.

// Stage Properties
    float* stage_tempo; // Optional. Tempo in BPM.
    Target_VideoState* stage_video_state; // Optional.
    float* stage_video_transparency; // Optional.
    Target_TTSLanguage* stage_tts_language; // Optional.

// Sprite Properties
    bool* sprite_is_visible; // Optional.
    int64_t* sprite_x; // Optional.
    int64_t* sprite_y; // Optional.
    float* sprite_size; // Optional. Size out of 100.
    float* sprite_direction; // Optional.
    bool* sprite_is_draggable; // Optional.
    Target_RotationStyle* sprite_rotation_style; // Optional.
} Project_Target;