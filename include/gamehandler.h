#pragma once
#include "includes.h"
#include "game.h"

void initGame(Game*);
void runGame(Game*);
void updateGame(Game*);
void renderGame(Game*);
void quitGame(Game*);

void mouseCallback(GLFWwindow*, int, int, int); 
