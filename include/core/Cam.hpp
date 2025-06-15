#pragma once
#include <raylib.h>

class Cam {

public:
    Cam(Vector2 target, Vector2 offset);
    
    void Update(Vector2 target);
    Camera2D GetCamera2D() const;

private:
    Camera2D camera;

};