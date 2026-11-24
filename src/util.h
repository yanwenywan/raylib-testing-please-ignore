#pragma once

#include "raylib.h"

/**
 * Given a camera with a world width and height, reeturn the necessary zoom to
 * fit it to the screen
 */
float calculateScreenZoom(int worldWidth, int worldHeight); 

/**
 * Creates a camera2d scaled so that the world fits the screen
 */
Camera2D initialiseScaledCamera(int worldWidth, int worldHeight); 

/**
 * Gets the mouse position and convert it to world coordinates
 */
Vector2 getMousePosWorld(Camera2D camera); 

/**
 * Gets the mouse (screen) position as (x, GetScreenHeight-y), 
 * suitable for passing into opengl
 */
Vector2 getMousePositionInvertedY();

/**
 * Gets the screen width/height as a vec2
 */
Vector2 getScreenSize();

