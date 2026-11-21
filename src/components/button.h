
#include "raylib.h"

typedef enum {
    B_NONE = 0, B_HOVER, B_PRESSED
} ButtonState;

/**
 * All the information needed to draw a text using raylib defaults
 */
typedef struct {
    int posX;
    int posY;
    int fontSize;
    Color color;
    char* text;
} SimpleText;

/**
 * Simple press button drawn using primitives
 * Assumes world space
 */
typedef struct {
    Rectangle rect;
    Color offColor;
    Color pressedColor;
    SimpleText label;
    void (*action)();
    ButtonState state;
} SimpleButton;

SimpleText makeTextSimple(char* text, int posX, int posY, int fontSize, Color color);

SimpleButton makeSimpleButton(Rectangle rect, void (*action)(), Color offColor, Color pressedColor, SimpleText label);

// button specific

/** Requires a camera2d env */
void Button_update(SimpleButton* this, Camera2D camera);

/** Assumes a camera2d env */
void Button_draw(SimpleButton* this);
