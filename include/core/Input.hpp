#pragma once

namespace Input {

    void Update();

    // Movement
    bool IsMoveForwardPressed();
    bool IsMoveBackwardPressed();

    bool IsMoveLeftPressed();
    bool IsMoveRightPressed();

    bool IsJumpPressed();
    bool IsRunHeld();

    // Hotbar
    int GetHotbarKeyPressed();
    
    // Interacts
    bool IsInteractPressed();
    bool IsUseLeftHandPressed();
    bool IsUseRightHandPressed();
    
    // Interface
    bool IsInventoryTogglePressed();
    bool IsPauseMenuPressed();
    bool IsMapTogglePressed();

    // Camera
    bool IsCameraTogglePressed();

}