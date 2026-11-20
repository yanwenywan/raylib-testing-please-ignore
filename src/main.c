#include "raylib.h"
#include "stb_ds.h"
#include <stdint.h>

typedef struct Dot {
    Vector2 pos;
    Color colour;
} Dot;

int main(void) {
    InitWindow(800, 450, "Raylib test window");
    SetTargetFPS(60);

    Dot* dots = NULL;

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Dot dot = { GetMousePosition(), ColorFromHSV((float)(arrlen(dots) % 360), 0.8f, 0.9f) };
            arrput(dots, dot);
        }

        if (IsKeyPressed(KEY_C)) {
            arrclear(dots);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < arrlen(dots); i++) {
            DrawCircleV(dots[i].pos, 4, dots[i].colour);
        }
        DrawText(TextFormat("dots: %d  (C to clear)", (int)arrlen(dots)), 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    arrfree(dots);
    CloseWindow();
    return 0;
}
