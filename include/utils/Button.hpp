#pragma once

#include <functional>
#include <string>

#include <raylib.h>

namespace utils {

struct Button {
    Rectangle bounds;
    std::string text;
    std::function<void()> onClick;

    void Update() {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), bounds)) if (onClick) onClick();
    }

    void Draw() {
        bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
        DrawRectangleRec(bounds, hovered ? WHITE : LIGHTGRAY);
        DrawText(text.c_str(), bounds.x + 10, bounds.y + 10, 20, BLACK);
    }    

};

}