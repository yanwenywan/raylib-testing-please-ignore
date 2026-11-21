#pragma once

#include "raylib.h"

typedef struct Dot {
    Vector2 pos;
    Color colour;
} Dot;

typedef struct Dots {
    Camera2D camera;
    Dot* dots;
} Dots;

void Dots_init(Dots* this);

void Dots_update(Dots* this);

void Dots_draw(Dots* this);

void Dots_unload(Dots* this);

