#include "menu.h"
#include "raylib.h"
#include "stb_ds.h"
#include "constants.h"
#include "dots.h"
#include <stdint.h>

void unloadScreen(Screen screen);
void loadScreen(Screen screen);

static Screen currentScreen = MENU_SCREEN;

static Dots dotsScreen;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 1000, "Raylib test window");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    loadScreen(currentScreen);

    while (!WindowShouldClose()) {
        switch (currentScreen) {
            case MENU_SCREEN:
                Menu_update();
                Menu_draw();
                break;
            case DOTS_SCREEN:
                Dots_update(&dotsScreen);
                Dots_draw(&dotsScreen);
                break;
        }
    }

    unloadScreen(currentScreen);
    
    CloseWindow();
    return 0;
}

void changeScreen(Screen screen) {
    unloadScreen(currentScreen);
    currentScreen = screen;
    loadScreen(screen);
}

void unloadScreen(Screen screen) {
    switch (screen) {
        case MENU_SCREEN:
            Menu_unload();
            break;
        case DOTS_SCREEN:
            Dots_unload(&dotsScreen);
            break;
    }
}

void loadScreen(Screen screen) {
    switch (screen) {
        case MENU_SCREEN:
            Menu_init();
            break;
        case DOTS_SCREEN:
            Dots_init(&dotsScreen);
            break;
    }
}
