#pragma once

/**
 * Adding a new screen:
 * 
 * in main.c, update unload, load, and the draw loop
 */
typedef enum Screen {
    MENU_SCREEN = 0,
    DOTS_SCREEN,
    SHADER_SCREEN
} Screen ;

/**
 * Unloads the old screen, loads the new screen
 */
void changeScreen(Screen screen);
