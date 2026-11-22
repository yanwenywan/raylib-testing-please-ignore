#include "menu.h"
#include "raylib.h"
#include "stb_ds.h"
#include "constants.h"
#include "dots.h"
#include "fragshadertoy.h"
#include <stdint.h>

void unloadScreen(Screen screen);
void loadScreen(Screen screen);

static Screen currentScreen = MENU_SCREEN;

static Dots dotsScreen;

int main(void) {
    // cd to the executable dir so assets are loaded properly
    ChangeDirectory(GetApplicationDirectory());
    if (!DirectoryExists("assets/") && DirectoryExists("../Resources/assets")) {
        ChangeDirectory("../Resources");  // macos bundled application
    } 
    if (!DirectoryExists("assets")) {
        TraceLog(LOG_FATAL, "Failed to find assets folder in %s, exiting.", GetWorkingDirectory());
        return 1;
    }
    
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
            case SHADER_SCREEN:
                FragShaderToy_update(GetFrameTime());
                FragShaderToy_draw();
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
        case SHADER_SCREEN:
            FragShaderToy_unload();
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
        case SHADER_SCREEN:
            FragShaderToy_init();
            break;
    }
}
