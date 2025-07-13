#include "core/Input.hpp"

#include <raylib.h>

namespace Input {
    
    void Update() {}

    // Movement
    bool IsMoveForwardPressed() { return IsKeyDown(KEY_W); }
    bool IsMoveBackwardPressed() { return IsKeyDown(KEY_S); }

    bool IsMoveLeftPressed() { return IsKeyDown(KEY_A); }
    bool IsMoveRightPressed() { return IsKeyDown(KEY_D); }

    bool IsJumpPressed() { return IsKeyDown(KEY_SPACE); }
    bool IsRunHeld() { return IsKeyDown(KEY_LEFT_SHIFT); }

    // Hotbar
    int GetHotbarKeyPressed() { 
        for (int i = 0; i < 6; i++) {
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

    // Camera
    bool IsCameraTogglePressed() { return IsKeyPressed(KEY_V); }

}