#include <raylib.h>
#include "core/Input.hpp"

namespace Input {
    
    void Update() {}
    bool IsMovingUp() { return IsKeyDown(KEY_W); }
    bool IsMovingLeft() { return IsKeyDown(KEY_A); }
    bool IsMovingDown() { return IsKeyDown(KEY_S); }
    bool IsMovingRight() { return IsKeyDown(KEY_D); }
    bool IsRunning() { return IsKeyDown(KEY_LEFT_SHIFT); }
    bool IsOpeningInventory() { return IsKeyPressed(KEY_E); }
    bool IsOpeningMenu() { return IsKeyPressed(KEY_ESCAPE); }

}