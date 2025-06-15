#pragma once

namespace Input {

    void Update();

    // Movement
    bool IsMoveUpPressed();
    bool IsMoveLeftPressed();
    bool IsMoveDownPressed();
    bool IsMoveRightPressed();
    bool IsRunHeld();
    
    // Interacts
    bool IsInteractPressed();
    bool IsUseLeftHandPressed();
    bool IsUseRightHandPressed();
    
    // Interface
    bool IsInventoryTogglePressed();
    bool IsPauseMenuPressed();
    bool IsMapTogglePressed();

}