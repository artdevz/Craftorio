#pragma once
#include <raylib.h>

class CameraManager {

public:
    CameraManager();
    
    void Update(Vector3 playerPosition);
    Camera3D GetCamera3D() const;

private:
    Camera3D camera;

};