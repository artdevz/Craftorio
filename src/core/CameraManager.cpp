#include "core/CameraManager.hpp"

CameraManager::CameraManager(Vector2 target, Vector2 offset) {
    camera.target = target;
    camera.offset = offset;
    camera.rotation = 0;
    camera.zoom = 2.0;
}

void CameraManager::Update(Vector2 target) { camera.target = target; }

Camera2D CameraManager::GetCamera2D() const { return camera; }