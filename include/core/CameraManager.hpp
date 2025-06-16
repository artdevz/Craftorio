#pragma once
#include <raylib.h>

class CameraManager {

public:
    CameraManager(Vector2 target, Vector2 offset);
    
    void Update(Vector2 target);
    Camera2D GetCamera2D() const;

private:
    Camera2D camera;

};