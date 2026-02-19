#pragma once
#include "player.h"
#include "game.h"

void initPlayer(Player*);
void handleTickPlayer(Game*, Player*);
void renderPlayer(Game*, Player*);
