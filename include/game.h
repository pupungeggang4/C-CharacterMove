#pragma once
#include "player.h"
#include "includes.h"

typedef struct Game {
    GLFWwindow* window;
    GLuint texturePlayer;
    Player player;
    float framePrevious, frameCurrent, delta;
    int windowWidth, windowHeight;
} Game;
