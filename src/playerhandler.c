#include "shape.h"
#include "player.h"
#include "game.h"
#include "playerhandler.h"

void initPlayer(Player* player) {
    player->rect = (Rect2){{0.f, 0.f}, {0.5f, 0.5f}};
    player->dest = (Vec2){0.f, 0.f};
    player->dir = (Vec2){0.f, 0.f};
    player->speed = 2.f;
    player->moving = 0;
    player->animState = 6;
    player->frameTime = 0.f;
    player->frameInterval = 0.2f;
    player->frames = 4;
    player->frameRect[0] = 0.125f;
    player->frameRect[1] = 0.125f;
    player->frameRect[2] = 0.125f;
    player->frameRect[3] = 0.125f;
}

void handleTickPlayer(Game* game, Player* player) {
    if (player->moving == 1) {
        Vec2 diff = {player->dest.x - player->rect.pos.x, player->dest.y - player->rect.pos.y};
        float norm = sqrt(diff.x * diff.x + diff.y * diff.y);
        if (norm > 0.05f) {
            player->dir.x = diff.x / norm;
            player->dir.y = diff.y / norm;
            if (fabs(player->dir.x) > fabs(player->dir.y)) {
                if (player->dir.x > 0) {
                    player->animState = 3;
                } else {
                    player->animState = 1;
                }
            } else {
                if (player->dir.y > 0) {
                    player->animState = 5;
                } else {
                    player->animState = 7;
                }
            }
            player->rect.pos.x += player->dir.x * player->speed * game->delta;
            player->rect.pos.y += player->dir.y * player->speed * game->delta;
        } else {
            player->moving = 0;
            if (player->animState == 1) player->animState = 0;
            else if (player->animState == 3) player->animState = 2;
            else if (player->animState == 5) player->animState = 4;
            else if (player->animState == 7) player->animState = 6;
        }
    }
}

void renderPlayer(Game* game, Player* player) {
    player->frameTime += game->delta;
    int frameCurrent = (int)(player->frameTime / player->frameInterval) % player->frames;
    int frameNo = player->animState * player->frames + frameCurrent;
    int frameRow = frameNo / 8;
    int frameCol = frameNo % 8;
    float textureRect[4] = {player->frameRect[0] * frameCol, player->frameRect[1] * frameRow, player->frameRect[2], player->frameRect[3]};

    glBegin(GL_QUADS);
    glTexCoord2f(textureRect[0], textureRect[1] + textureRect[3]);
    glVertex2f(player->rect.pos.x - player->rect.size.x / 2.f, player->rect.pos.y - player->rect.size.y / 2.f);
    glTexCoord2f(textureRect[0], textureRect[1]);
    glVertex2f(player->rect.pos.x - player->rect.size.x / 2.f, player->rect.pos.y + player->rect.size.y / 2.f);
    glTexCoord2f(textureRect[0] + textureRect[2], textureRect[1]);
    glVertex2f(player->rect.pos.x + player->rect.size.x / 2.f, player->rect.pos.y + player->rect.size.y / 2.f);
    glTexCoord2f(textureRect[0] + textureRect[2], textureRect[1] + textureRect[3]);
    glVertex2f(player->rect.pos.x + player->rect.size.x / 2.f, player->rect.pos.y - player->rect.size.y / 2.f);
    glEnd();
}

