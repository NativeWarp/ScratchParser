#pragma once

#include "./fields/fields.h"
#include "./input/input.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum Block_OpCode {
// Motion Blocks
    OpCode_Motion_MoveSteps, // move () steps
    OpCode_Motion_TurnRight, // turn right () degrees
    OpCode_Motion_TurnLeft, // turn left () degrees
    OpCode_Motion_GoTo, // go to ()
    OpCode_Motion_GoToXY, // go to x: () y: ()
    OpCode_Motion_GlideTo, // glide () secs to ()
    OpCode_Motion_GlideSecondsToXY, // glide () secs to x: () y: () 
    OpCode_Motion_PointInDirection, // point in direction ()
    OpCode_Motion_PointTowards, // point towards ()
    OpCode_Motion_ChangeXBy, // change x by ()
    OpCode_Motion_SetX, // set x to ()
    OpCode_Motion_ChangeYBy, // change y by ()
    OpCode_Motion_SetY, // set y to ()
    OpCode_Motion_IfOnEdgeBounce, // if on edge, bounce
    OpCode_Motion_SetRotationStyle, // set rotation style ()
    OpCode_Motion_XPosition, // x position
    OpCode_Motion_YPosition, // y position
    OpCode_Motion_Direction, // direction
    OpCode_Motion_ScrollRight, // Hidden - scroll right ()
    OpCode_Motion_ScrollUp, // Hidden - scroll up ()
    OpCode_Motion_XScroll, // Hidden - x scroll
    OpCode_Motion_YScroll, // Hidden - y scroll

// Looks Blocks
    OpCode_Looks_SayForSeconds, // say () for () seconds
    OpCode_Looks_Say, // say ()
    OpCode_Looks_ThinkForSeconds, // think () for () seconds
    OpCode_Looks_Think, // think ()
    OpCode_Looks_SwitchCostumeTo, // switch costume to ()
    OpCode_Looks_NextCostume, // next costume
    OpCode_Looks_SwitchBackdropTo, // switch backdrop to ()
    OpCode_Looks_SwitchBackdropToAndWait, // switch backdrop to () and wait
    OpCode_Looks_NextBackdrop, // next backdrop
    OpCode_Looks_ChangeSizeBy, // change size by ()
    OpCode_Looks_SetSizeTo, // set size to () %
    OpCode_Looks_ChangeEffectBy, // change () effect by ()
    OpCode_Looks_SetEffectTo, // set () effect to ()
    OpCode_Looks_ClearGraphicEffects, // clear graphic effects.
    OpCode_Looks_Show, // show
    OpCode_Looks_Hide, // hide
    OpCode_Looks_GoToFrontBack, // go to () layer
    OpCode_Looks_GoForwardBackwardLayers, // go () () layers
    OpCode_Looks_Costume, // costume ()
    OpCode_Looks_Backdrop, // backdrop ()
    OpCode_Looks_Size, // size
    OpCode_Looks_HideAllSprites, // Hidden - hide all sprites
    OpCode_Looks_SetStretchTo, // Hidden - set stretch to () %
    OpCode_Looks_ChangeStretchBy, // Hidden - change stretch by ()

// Sounds Blocks
    OpCode_Sound_PlayUntilDone, // play sound () until done
    OpCode_Sound_Play, // start sound ()
    OpCode_Sound_StopAllSounds, // stop all sounds
    OpCode_Sound_ChangeEffectBy, // change () effect by ()
    OpCode_Sound_SetEffectTo, // set () effect to ()
    OpCode_Sound_ClearSoundEffects, // clear sound effects
    OpCode_Sound_ChangeVolumeBy, // change volume by ()
    OpCode_Sound_SetVolumeTo, // set volume to () %
    OpCode_Sound_Volume, // volume

// Event Blocks
    OpCode_Event_WhenFlagClicked, // when flag clicked
    OpCode_Event_WhenKeyPressed, // when () key pressed
    OpCode_Event_WhenThisSpriteClicked, // when this sprite clicked
    OpCode_Event_WhenStageClicked, // when stage clicked
    OpCode_Event_WhenBackdropSwitchesTo, // when backdrop switches to ()
    OpCode_Event_WhenGreaterThan, // when () > ()
    OpCode_Event_WhenBroadcastRecieved, // when I recieve ()
    OpCode_Event_Broadcast, // broadcast ()
    OpCode_Event_BroadcastAndWait, // broadcast () and wait
    OpCode_Event_WhenTouchingObject, // Hidden - when this sprite touches ()

// Control Blocks
    OpCode_Control_Wait, // wait () seconds
    OpCode_Control_Repeat, // repeat ()
    OpCode_Control_Forever, // forever
    OpCode_Control_If, // if () then
    OpCode_Control_IfElse, // if () then, else
    OpCode_Control_WaitUntil, // wait until ()
    OpCode_Control_RepeatUntil, // repeat until ()
    OpCode_Control_Stop, // stop ()
    OpCode_Control_StartAsClone, // when I start as a clone
    OpCode_Control_CreateCloneOf, // create clone of ()
    OpCode_Control_DeleteThisClone, // delete this clone
    OpCode_Control_ForEach, // Hidden - for each () in ()
    OpCode_Control_While, // Hidden - while ()
    OpCode_Control_GetCounter, // Hidden - counter
    OpCode_Control_IncrementCounter, // Hidden - increment counter
    OpCode_Control_ClearCounter, // Hidden - clear counter
    OpCode_Control_AllAtOnce, // Hidden - all at once

// Sensing Blocks
    OpCode_Sensing_TouchingObject, // touching () ?
    OpCode_Sensing_TouchingColor, // touching color () ?
    OpCode_Sensing_ColorIsTouchingColor, // color () is touching () ?
    OpCode_Sensing_DistanceTo, // distance to ()
    OpCode_Sensing_AskAndWait, // ask () and wait
    OpCode_Sensing_Answer, // answer
    OpCode_Sensing_KeyPressed, // key () pressed?
    OpCode_Sensing_MouseDown, // mouse down?
    OpCode_Sensing_MouseX, // mouse x
    OpCode_Sensing_MouseY, // mouse y
    OpCode_Sensing_SetDragMode, // set drag mode ()
    OpCode_Sensing_Loudness, // loudness
    OpCode_Sensing_Timer, // timer
    OpCode_Sensing_ResetTimer, // reset timer
    OpCode_Sensing_Of, // () of ()
    OpCode_Sensing_Current, // current ()
    OpCode_Sensing_DaysSince2000, // days since 2000
    OpCode_Sensing_Online, // online?
    OpCode_Sensing_Username, // username
    OpCode_Sensing_Loud, // Hidden - loud?
    OpCode_Sensing_UserID, // Hidden - user id

// Operator Blocks
    OpCode_Operator_Add, // () + ()
    OpCode_Operator_Subtract, // () - ()
    OpCode_Operator_Multiply, // () * ()
    OpCode_Operator_Divide, // () / ()
    OpCode_Operator_Random, // pick random () to ()
    OpCode_Operator_GreaterThan, // () > ()
    OpCode_Operator_LessThan, // () < ()
    OpCode_Operator_Equals, // () = ()
    OpCode_Operator_And, // () and ()
    OpCode_Operator_Or, // () or ()
    OpCode_Operator_Not, // not ()
    OpCode_Operator_Join, // join () ()
    OpCode_Operator_LetterOf, // letter () of ()
    OpCode_Operator_Length, // length of ()
    OpCode_Operator_Contains, // () contains () ?
    OpCode_Operator_Mod, // () mod ()
    OpCode_Operator_Round, // round ()
    OpCode_Operator_Math, // () of ()

// Variable Blocks
    OpCode_Data_Variable,
    OpCode_Data_Variable_SetVariableTo, // set () to ()
    OpCode_Data_Variable_ChangeVariableBy, // change () by ()
    OpCode_Data_Variable_ShowVariable, // show variable ()
    OpCode_Data_Variable_HideVariable, // hide variable ()

// List Blocks
    OpCode_Data_List,
    OpCode_Data_List_AddToList, // add () to ()
    OpCode_Data_List_DeleteOfList, // delete () of ()
    OpCode_Data_List_DeleteAllOfList, // delete all of ()
    OpCode_Data_List_InsertAtList, // insert () at () of ()
    OpCode_Data_List_ReplaceItemOfList, // replace item () of () with ()
    OpCode_Data_List_ItemOfList, // item () of ()
    OpCode_Data_List_ItemNumberOfList, // item # of () in ()
    OpCode_Data_List_LengthOfList, // length of ()
    OpCode_Data_List_ListContainsItem, // () contains () ?
    OpCode_Data_List_ShowList, // show list ()
    OpCode_Data_List_HideList, // hide list ()
    OpCode_Data_List_IndexAll, // Hidden
    OpCode_Data_List_IndexRandom, // Hidden

// My Blocks
    OpCode_Procedures_Definition,
    OpCode_Procedures_Call,
    OpCode_Procedures_ArgumentStringNumber,
    OpCode_Procedures_ArgumentBoolean,

// Music Extension Blocks
    OpCode_Extension_Music_PlayDrumForBeats, // play drum () for () beats
    OpCode_Extension_Music_RestForBeats, // rest for () beats
    OpCode_Extension_Music_PlayNoteForBeats, // play note () for () beats
    OpCode_Extension_Music_SetInstrument, // set instrument to ()
    OpCode_Extension_Music_SetTempo, // set tempo to ()
    OpCode_Extension_Music_ChangeTempo, // change tempo by ()
    OpCode_Extension_Music_GetTempo, // tempo
    OpCode_Extension_Music_MidiPlayDrumForBeats, // Hidden - play drum () for () beats
    OpCode_Extension_Music_MidiSetInstrument, // Hidden - set instrument to ()
    
// Pen Extension Blocks
    OpCode_Extension_Pen_Clear, // clear
    OpCode_Extension_Pen_Stamp, // stamp
    OpCode_Extension_Pen_PenDown, // pen down
    OpCode_Extension_Pen_PenUp, // pen up
    OpCode_Extension_Pen_SetPenColor, // set pen color to ()
    OpCode_Extension_Pen_ChangePenColorParamBy, // change pen () by ()
    OpCode_Extension_Pen_SetPenColorParamTo, // set pen () to ()
    OpCode_Extension_Pen_ChangePenSizeBy, // change pen size by ()
    OpCode_Extension_Pen_SetPenSizeTo, // set pen size to ()
    OpCode_Extension_Pen_SetPenHueToNumber, // Hidden - set pen color to ()
    OpCode_Extension_Pen_ChangePenHueBy, // Hidden - change pen color by ()
    OpCode_Extension_Pen_SetPenShadeToNumber, // Hidden - set pen shade to ()
    OpCode_Extension_Pen_ChangePenShadeBy, // Hidden - change pen shade by ()

// Video Sensing Extension Blocks
    OpCode_Extension_VideoSensing_WhenMotionGreaterThan, // when video motion > ()
    OpCode_Extension_VideoSensing_VideoOn, // video () on ()
    OpCode_Extension_VideoSensing_VideoToggle, // turn video ()
    OpCode_Extension_VideoSensing_SetVideoTransparency, // set video transparency to ()
    
// Face Sensing Extension Blocks
    OpCode_Extension_FaceSensing_GoToPart, // go to ()
    OpCode_Extension_FaceSensing_PointInFaceTiltDirection, // point in direction of face tilt
    OpCode_Extension_FaceSensing_SetSizeToFaceSize, // set size to face size
    OpCode_Extension_FaceSensing_WhenTilted, // when face tilts ()
    OpCode_Extension_FaceSensing_WhenSpriteTouchesPart, // when this sprite touches a ()
    OpCode_Extension_FaceSensing_WhenFaceDetected, // when a face is detected
    OpCode_Extension_FaceSensing_FaceIsDetected, // a face is detected?
    OpCode_Extension_FaceSensing_FaceTilt, // face tilt
    OpCode_Extension_FaceSensing_FaceSize, // face size

// Text To Speech Extension Blocks
    OpCode_Extension_TextToSpeech_SpeakAndWait, // speak ()
    OpCode_Extension_TextToSpeech_SetVoice, // set voice to ()
    OpCode_Extension_TextToSpeech_SetLanguage, // set language to ()

// Translate Extension Blocks
    OpCode_Extension_Translate_GetTranslate, // translate () to ()
    OpCode_Extension_Translate_GetViewerLanguage, // language

// MakeyMakey Extension Blocks
    OpCode_Extension_MakeyMakey_WhenMakeyKeyPressed, // when () key pressed
    OpCode_Extension_MakeyMakey_WhenCodePressed, // when () pressed in order

// micro:bit Extension Blocks
    OpCode_Extension_MicroBit_WhenButtonPressed, // when () button pressed
    OpCode_Extension_MicroBit_IsButtonPressed, // () button pressed?
    OpCode_Extension_MicroBit_WhenGesture, // when ()
    OpCode_Extension_MicroBit_DisplaySymbol, // display ()
    OpCode_Extension_MicroBit_DisplayText, // display text
    OpCode_Extension_MicroBit_DisplayClear, // clear display
    OpCode_Extension_MicroBit_WhenTilted, // when tilted ()
    OpCode_Extension_MicroBit_IsTilted, // tilted () ?
    OpCode_Extension_MicroBit_GetTiltAngle, // tilt angle ()
    OpCode_Extension_MicroBit_WhenPinConnected, // when pin () connected

// Go Direct Force & Acceleration Extension Blocks
    OpCode_Extension_GoDirectForceAcceleration_WhenGesture, // when ()
    OpCode_Extension_GoDirectForceAcceleration_WhenForcePushedOrPulled, // when force sensor ()
    OpCode_Extension_GoDirectForceAcceleration_GetForce, // force
    OpCode_Extension_GoDirectForceAcceleration_WhenTilted, // when tilted ()
    OpCode_Extension_GoDirectForceAcceleration_IsTilted, // tilted () ?
    OpCode_Extension_GoDirectForceAcceleration_GetTilt, // tilt angle ()
    OpCode_Extension_GoDirectForceAcceleration_IsFreeFalling, // falling?
    OpCode_Extension_GoDirectForceAcceleration_GetSpinSpeed, // spin speed ()
    OpCode_Extension_GoDirectForceAcceleration_GetAcceleration, // acceleration ()

// LEGO MINDSTORMS EV3 Extension Blocks
    OpCode_Extension_LegoEV3_MotorTurnClockwise, // motor () turn this way for () seconds
    OpCode_Extension_LegoEV3_MotorTurnCounterClockwise, // motor () turn that way for () seconds
    OpCode_Extension_LegoEV3_MotorSetPower, // motor () set power () %
    OpCode_Extension_LegoEV3_GetMotorPosition, // motor () position
    OpCode_Extension_LegoEV3_WhenButtonPressed, // button () pressed
    OpCode_Extension_LegoEV3_WhenDistanceLessThan, // when distance < ()
    OpCode_Extension_LegoEV3_WhenBrightnessLessThan, // when brightness < ()
    OpCode_Extension_LegoEV3_ButtonPressed, // button () pressed?
    OpCode_Extension_LegoEV3_GetDistance, // distance
    OpCode_Extension_LegoEV3_GetBrightness, // brightness
    OpCode_Extension_LegoEV3_Beep, // beep note () for () secs

// LEGO BOOST Extension Blocks
    OpCode_Extension_LegoBoost_MotorOnFor, // turn motor () for () seconds
    OpCode_Extension_LegoBoost_MotorOnForROtation, // turn motor () for () rotations
    OpCode_Extension_LegoBoost_MotorOn, // turn motor () on
    OpCode_Extension_LegoBoost_MotorOff, // turn motor () off
    OpCode_Extension_LegoBoost_SetMotorPower, // set motor () speed to () %
    OpCode_Extension_LegoBoost_SetMotorDirection, // set motor () direction ()
    OpCode_Extension_LegoBoost_GetMotorPosition, // motor () position
    OpCode_Extension_LegoBoost_WhenColor, // when () brick seen
    OpCode_Extension_LegoBoost_SeeingColor, // seeing () brick?
    OpCode_Extension_LegoBoost_WhenTilted, // when tilted ()
    OpCode_Extension_LegoBoost_GetTiltAngle, // tilt angle ()
    OpCode_Extension_LegoBoost_SetLightHue, // set light color to ()

// Music Education WeDo 2.0 Extension Blocks
    OpCode_Extension_LegoWeDo2_MotorOnFor, // turn () on for () seconds
    OpCode_Extension_LegoWeDo2_MotorOn, // turn () on
    OpCode_Extension_LegoWeDo2_MotorOff, // turn () off
    OpCode_Extension_LegoWeDo2_StartMotorPower, // set () power to ()
    OpCode_Extension_LegoWeDo2_SetMotorDirection, // set () direction to ()
    OpCode_Extension_LegoWeDo2_SetLightHue, // set light color to ()
    OpCode_Extension_LegoWeDo2_WhenDistance, // when distance () ()
    OpCode_Extension_LegoWeDo2_WhenTilted, // when tilted ()
    OpCode_Extension_LegoWeDo2_GetDistance, // distance
    OpCode_Extension_LegoWeDo2_IsTilted, // tilted ()
    OpCode_Extension_LegoWeDo2_GetTiltAngle, // tilt angle ()
    OpCode_Extension_LegoWeDo2_PlayNoteFor, // Hidden - play note () for () seconds

// Example Blocks
    OpCode_CoreExample_ExampleOpcode, // Hidden - example block
    OpCode_CoreExample_ExampleWithInlineImage, // Hidden - block with image inline

// Undefined Blocks
    OpCode_CoreExample_Undefined // Hidden
} Block_OpCode;

// A physical Block in a Target
typedef struct Target_Block {
    const char* id; // Internal ID.
    Block_OpCode opcode;

    struct Target_Block* next; // Optional. The following block.
    struct Target_Block* parent; // Optional. The preceding stack block, parent c block, or containing block with input.

    Block_Input* inputs; // Array of inputs.
    Block_Fields* fields; // Array of fields.

    int64_t* x; // Optional. Only included if block is top level.
    int64_t* y; // Optional. Only included if block is top level.

    struct Target_Comment* comment; // Optional.
    struct Block_Mutation* mutation; // Optional. Block mutations pertaining to a project's custom blocks.
} Target_Block;