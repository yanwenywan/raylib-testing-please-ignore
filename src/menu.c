#include "raylib.h"
#include "stb_ds.h"
#include "util.h"
#include "constants.h"
#include "components/button.h"
#include "menu.h"

static const int WORLD_WIDTH = 1600;
static const int WORLD_HEIGHT = 1000;

static Camera2D camera;
static SimpleButton* buttonArrayList;

void switchToDotsScreen();

void Menu_init() {
    camera = initialiseScaledCamera(WORLD_WIDTH, WORLD_HEIGHT);

    arrput(buttonArrayList, makeSimpleButton(
        (Rectangle){40, 100, 300, 120}, 
        &switchToDotsScreen, 
        PURPLE, RED, 
        makeTextSimple("Dots", 50, 110, 30, WHITE)
    ));
}

void Menu_update() {
    if (IsWindowResized()) {
        camera.zoom = calculateScreenZoom(WORLD_WIDTH, WORLD_HEIGHT);
    }
    
    for (int i = 0; i < arrlen(buttonArrayList); i++) {
        Button_update(&buttonArrayList[i], camera);
    }
}

void Menu_draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    DrawText("Menu of raylib experiments", 40, 40, 36, DARKGRAY);

    for (int i = 0; i < arrlen(buttonArrayList); i++) {
        Button_draw(&buttonArrayList[i]);
    }
    
    EndMode2D();
    EndDrawing();
}

void Menu_unload() {
    arrfree(buttonArrayList);
}

void switchToDotsScreen() {
    changeScreen(DOTS_SCREEN);
}
