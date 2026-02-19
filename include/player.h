#pragma once
#include "shape.h"

typedef struct Player {
    Rect2 rect;
    Vec2 dest;
    Vec2 dir;
    float speed;
    int moving;
    int animState, frames;
    float frameTime, frameInterval;
    float frameRect[4]; 
} Player;
