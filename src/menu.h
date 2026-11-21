#pragma once 

#include "raylib.h"

typedef struct Menu {
    Camera2D camera;
} Menu ;

void Menu_init();

void Menu_update();

void Menu_draw();

void Menu_unload();
