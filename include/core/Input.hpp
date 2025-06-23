#pragma once

namespace Input {

    void Update();

    // Movement
    bool IsMoveUpPressed();
    bool IsMoveLeftPressed();
    bool IsMoveDownPressed();
    bool IsMoveRightPressed();
    bool IsSpacePressed();
    bool IsRunHeld();

    // Hotbar
    int IsHotbarKeyPressed();
    
    // Interacts
    bool IsInteractPressed();
    bool IsUseLeftHandPressed();
    bool IsUseRightHandPressed();
    
    // Interface
    bool IsInventoryTogglePressed();
    bool IsPauseMenuPressed();
    bool IsMapTogglePressed();

}