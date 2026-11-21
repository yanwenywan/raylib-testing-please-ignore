#include "raylib.h"
#include "stb_ds.h"
#include "dots.h"
#include <stdint.h>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 1000, "Raylib test window");
    SetTargetFPS(60);

    Dots dotsScreen;
    Dots_init(&dotsScreen);

    while (!WindowShouldClose()) {
        Dots_update(&dotsScreen);
        Dots_draw(&dotsScreen);
    }

    Dots_unload(&dotsScreen);
    CloseWindow();
    return 0;
}
