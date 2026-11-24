#include "util.h"
#include "raylib.h"
#include <math.h>

float calculateScreenZoom(int worldWidth, int worldHeight) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float widthRatio = (float)screenWidth / (float)worldWidth;
    float heightRatio = (float)screenHeight / (float)worldHeight;

    // return fminf(widthRatio, heightRatio);
    return fmaxf(widthRatio, heightRatio);
}

Camera2D initialiseScaledCamera(int worldWidth, int worldHeight) {
    Camera2D camera = {
        (Vector2){0, 0},
        (Vector2){0, 0},
        0.0f,
        calculateScreenZoom(worldWidth, worldHeight)
    };
    return camera;
}

Vector2 getMousePosWorld(Camera2D camera) {
    Vector2 mouseScreenPos = GetMousePosition();
    Vector2 mouseWorldPos = GetScreenToWorld2D(mouseScreenPos, camera);
    return mouseWorldPos;
}

Vector2 getMousePositionInvertedY() {
    Vector2 mousePos = GetMousePosition();
    mousePos.y = GetScreenHeight() - mousePos.y;
    return mousePos;
}

Vector2 getScreenSize() {
    return (Vector2){(float)GetScreenWidth(), (float)GetScreenHeight()};
}
