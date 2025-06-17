#include <raylib.h>
#include "core/Input.hpp"

namespace Input {
    
    void Update() {}

    // Movement
    bool IsMoveUpPressed() { return IsKeyDown(KEY_W); }
    bool IsMoveLeftPressed() { return IsKeyDown(KEY_A); }
    bool IsMoveDownPressed() { return IsKeyDown(KEY_S); }
    bool IsMoveRightPressed() { return IsKeyDown(KEY_D); }
    bool IsRunHeld() { return IsKeyDown(KEY_LEFT_SHIFT); }

    // Hotbar
    int IsHotbarKeyPressed() { 
        for (int i = 0; i < 4; i++) {
            if (IsKeyDown(KEY_ONE + i)) return i;
        }
        return -1;
    }
    
    // Interacts
    bool IsInteractPressed() { return IsKeyPressed(KEY_E); }
    bool IsUseLeftHandPressed() { return IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }
    bool IsUseRightHandPressed() { return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT); }
    
    // Interface
    bool IsInventoryTogglePressed() { return IsKeyPressed(KEY_I); }
    bool IsPauseMenuPressed() { return IsKeyPressed(KEY_ESCAPE); }
    bool IsMapTogglePressed() { return IsKeyPressed(KEY_M); }

}