#include "includes.h"
#include "game.h"
#include "gamehandler.h"

void initGame(Game* game) {
    if (!glfwInit()) {
        return;
    }

    game->window = glfwCreateWindow(800, 600, "GLFW Character Movement", NULL, NULL);

    if (!game->window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(game->window);
    glfwSwapInterval(1);

    runGame(game);
}

void runGame(Game* game) {
    while (!glfwWindowShouldClose(game->window)) {
        glViewport(0, 0, 800, 600);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(game->window);
        glfwPollEvents();
    }
}

void updateGame(Game* game) {

}

void renderGame(Game* game) {

}

void quitGame(Game* game) {
    glfwDestroyWindow(game->window);
    glfwTerminate();
}
