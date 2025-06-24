#include "core/CameraManager.hpp"
#include <raymath.h>

CameraManager::CameraManager() {
    camera.position = { 15.0f, 15.0f, 15.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void CameraManager::Update(Vector3 playerPosition) { 
    camera.target = playerPosition;
    camera.position = Vector3Add(playerPosition, (Vector3){15.0f, 15.0f, 15.0f});
}

Camera3D CameraManager::GetCamera3D() const { return camera; }