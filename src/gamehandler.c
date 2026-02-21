
#include "includes.h"
#include "playerhandler.h"
#include "game.h"
#include "gamehandler.h"

void initGame(Game* game) {
    // GLFW setting part.
    if (!glfwInit()) {
        return;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    float xscale, yscale;

    if (!monitor) {
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
    #ifdef __APPLE__
    xscale = 1.f; yscale = 1.f;
    #endif
    game->windowWidth = 800 * xscale;
    game->windowHeight = 600 * yscale;
    game->window = glfwCreateWindow(game->windowWidth, game->windowHeight, "GLFW Character Movement", NULL, NULL);

    if (!game->window) {
        glfwTerminate();
        return;
    }

    int width, height;
    glfwGetFramebufferSize(game->window, &width, &height);

    glfwSetWindowAspectRatio(game->window, 4, 3);
    glfwSetWindowUserPointer(game->window, game);
    glfwSetMouseButtonCallback(game->window, mouseCallback);

    glfwMakeContextCurrent(game->window);
    glfwSwapInterval(1);

    glViewport(0, 0, width, height);
    glOrtho(-4.f, 4.f, -3.f, 3.f, -1.f, 1.f);
    glClearColor(0.5f, 1.f, 0.5f, 1.f);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &game->texturePlayer);
    glBindTexture(GL_TEXTURE_2D, game->texturePlayer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int tWidth, tHeight, tChannels;
    unsigned char *imgData = stbi_load("asset/sprite_player.png", &tWidth, &tHeight, &tChannels, 0);
    if (!imgData) {
        glfwTerminate();
        return;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tWidth, tHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    stbi_image_free(imgData);

    // Game variable.
    game->frameCurrent = 0.f;
    game->framePrevious = 0.f;
    game->delta = 0.f;

    // Player setting part.
    initPlayer(&game->player);

    runGame(game);
}

void runGame(Game* game) {
    while (!glfwWindowShouldClose(game->window)) {
        game->frameCurrent = (float)glfwGetTime();
        game->delta = game->frameCurrent - game->framePrevious;
        game->framePrevious = game->frameCurrent;
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        updateGame(game);
        renderGame(game);
        glfwSwapBuffers(game->window);
        glfwPollEvents();
    }
}

void updateGame(Game* game) {
    handleTickPlayer(game, &game->player);
}

void renderGame(Game* game) {
    renderPlayer(game, &game->player);
}

void quitGame(Game* game) {
    glfwDestroyWindow(game->window);
    glfwTerminate();
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
    Game* game = glfwGetWindowUserPointer(window);
    double xpos, ypos;
    int width, height;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);
    float screenX = xpos / width * 8.f - 4.f;
    float screenY = ypos / height * -6.f + 3.f;

    game->player.dest.x = screenX;
    game->player.dest.y = screenY;
    printf("%.1f %.1f\n", screenX, screenY);
    game->player.moving = 1;
}
