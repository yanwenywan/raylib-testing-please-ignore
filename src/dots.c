#include "dots.h"
#include "constants.h"
#include "raylib.h"
#include "raymath.h"
#include "stb_ds.h"
#include "util.h"
#include <stdio.h>

static const int WORLD_WIDTH = 1600;
static const int WORLD_HEIGHT = 1000;

void Dots_init(Dots *this) {
    *this = (Dots){ 0 };
    
    this->camera = initialiseScaledCamera(WORLD_WIDTH, WORLD_HEIGHT);
}

void Dots_update(Dots *this) {
    if (IsWindowResized()) {
        this->camera.zoom = calculateScreenZoom(WORLD_WIDTH, WORLD_HEIGHT);
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        changeScreen(MENU_SCREEN);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouseScreenPos = GetMousePosition();
        Vector2 mouseWorldPos = GetScreenToWorld2D(mouseScreenPos, this->camera);
        printf("Mouse clicked at screen(%.1f, %.1f) world(%.1f, %.1f)\n",
            mouseScreenPos.x, mouseScreenPos.y, mouseWorldPos.x, mouseWorldPos.y);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // if equal to last, do not create
        if (arrlen(this->dots) == 0 || !Vector2Equals(getMousePosWorld(this->camera), arrlast(this->dots).pos)) {
            Dot dot = { getMousePosWorld(this->camera), ColorFromHSV((float)(arrlen(this->dots) % 360), 0.8f, 0.9f) };
            arrput(this->dots, dot);
        }
    }

    if (IsKeyPressed(KEY_C)) {
        arrclear(this->dots);
    }
}

void Dots_draw(Dots *this) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    BeginMode2D(this->camera);
    for (int i = 0; i < arrlen(this->dots); i++) {
        DrawCircleV(this->dots[i].pos, 4, this->dots[i].colour);
    }
    DrawText(TextFormat("dots: %d  (C to clear)", (int)arrlen(this->dots)), 10, 10, 20, DARKGRAY);
    EndMode2D();
    
    EndDrawing();
}

void Dots_unload(Dots *this) {
    arrfree(this->dots);
}

