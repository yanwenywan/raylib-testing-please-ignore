#pragma once

#include "raylib.h"

/**
 * Given a camera with a world width and height, reeturn the necessary zoom to
 * fit it to the screen
 */
float calculateScreenZoom(int worldWidth, int worldHeight); 

/**
 * Gets the mouse position and convert it to world coordinates
 */
Vector2 getMousePosWorld(Camera2D camera); 

