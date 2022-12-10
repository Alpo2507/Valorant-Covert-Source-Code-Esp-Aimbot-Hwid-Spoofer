#pragma once

enum InjectedInputMouseOptions
{
    Absolute = 32768,
    HWheel = 4096,
    LeftDown = 2,
    LeftUp = 4,
    MiddleDown = 32,
    MiddleUp = 64,
    Move = 1,
    MoveNoCoalesce = 8192,
    None = 0,
    RightDown = 8,
    RightUp = 16,
    VirtualDesk = 16384,
    Wheel = 2048,
    XDown = 128,
    XUp = 256
};

typedef struct _InjectedInputMouseInfo
{
    int DeltaX;
    int DeltaY;
    unsigned int MouseData;
    InjectedInputMouseOptions MouseOptions;
    unsigned int TimeOffsetInMilliseconds;
    void* ExtraInfo;
} InjectedInputMouseInfo;

bool mouseLoaded;

typedef bool (WINAPI* InjectMouseInput_t)(InjectedInputMouseInfo* inputs, int count);

InjectMouseInput_t InjectMouseInput;