#include "button.h"
#include "raylib.h"

SimpleText makeSimpleText(char *text, int posX, int posY, int fontSize, Color color) {
    SimpleText out = { posX, posY, fontSize, color, text };
    return out;
}

SimpleButton makeSimpleButton(Rectangle rect, void (*action)(void), Color offColor, Color pressedColor, SimpleText label) {
    SimpleButton out = { rect, offColor, pressedColor, label, action, B_NONE };
    return out;
}

void SimpleText_draw(SimpleText *this) {
    DrawText(this->text, this->posX, this->posY, this->fontSize, this->color);
}

void Button_update(SimpleButton *this, Camera2D camera) {
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    bool colliding = CheckCollisionPointRec(mouseWorld, this->rect);
    int button = MOUSE_BUTTON_LEFT;

    if (IsMouseButtonUp(button)) {
        this->state = colliding ? B_HOVER : B_NONE;
    }
    else if (IsMouseButtonDown(button) && colliding) {
        this->state = B_PRESSED;
    }

    if (IsMouseButtonReleased(button) && colliding) {
        this->action();
    }
}

void Button_draw(SimpleButton *this) {
    Color color;
    switch (this->state) {
        case B_NONE:
            color = this->offColor; break;
        case B_HOVER:
            color = ColorLerp(this->offColor, WHITE, .2f); break;
        case B_PRESSED:
            color = this->pressedColor; break;
    }

    DrawRectangleRec(this->rect, color);

    SimpleText label = this->label;
    DrawText(label.text, label.posX, label.posY, label.fontSize, label.color);
}
