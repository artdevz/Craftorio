#pragma once
#include <raylib.h>

class CameraManager {

public:
    CameraManager();
    
    void Update(Vector3 playerPosition, float deltaTime);
    Camera3D GetCamera3D() const;
    bool IsFirstPerson() const;
    Vector3 GetForward() const;

private:
    Camera3D camera;
    bool isFirstPerson;

    float yaw, pitch;       
    float distanceToPlayer; 

    void UpdateFPS(Vector3 playerPosition);
    void UpdateTPS(Vector3 playerPosition);

};