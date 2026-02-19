#include "includes.h"
#include "game.h"
#include "gamehandler.h"

int main() {
    Game game = {0};
    initGame(&game);
    runGame(&game);
    quitGame(&game);
    return 0;
}
