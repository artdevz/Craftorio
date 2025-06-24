#include "core/CameraManager.hpp"
#include "core/Input.hpp"
#include <raymath.h>

CameraManager::CameraManager() : 
    isFirstPerson(true), yaw(0.0f), pitch(0.0f), distanceToPlayer(10.0f) {
    camera.position = { 0.0f, 0.0f, 0.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor();
}

void CameraManager::Update(Vector3 playerPosition, float deltaTime) { 
    if (Input::IsCameraTogglePressed()) isFirstPerson = !isFirstPerson;

    Vector2 mouseDelta = GetMouseDelta();
    float sensibility = 5.0f;
    yaw -= mouseDelta.x * 0.003f * sensibility;
    pitch -= mouseDelta.y * 0.003f * sensibility;

    DrawText(TextFormat("Yaw: %.2f", yaw), 10, 140, 20, WHITE);
    DrawText(TextFormat("Pitch: %.2f", pitch), 10, 170, 20, WHITE);
    Vector3 dir = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    DrawText(TextFormat("Dir X: %.2f, Y: %.2f, Z: %.2f", dir.x, dir.y, dir.z), 10, 200, 20, WHITE);    

    pitch = Clamp(pitch, -PI / 2.2f, PI / 2.2f);

    if (isFirstPerson) {
        SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
        UpdateFPS(playerPosition);
    }
    else UpdateTPS(playerPosition);
}

void CameraManager::UpdateFPS(Vector3 playerPosition) {
    Vector3 direction = { 
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw) 
    };

    camera.position = { playerPosition.x, playerPosition.y + 1.8f, playerPosition.z };
    camera.target = Vector3Add(camera.position, direction);
    camera.up = { 0.0f, 1.0f, 0.0f };
}

void CameraManager::UpdateTPS(Vector3 playerPosition) {
    Vector3 offset = { 
        distanceToPlayer * cosf(pitch) * sinf(yaw),
        distanceToPlayer * sinf(pitch),
        distanceToPlayer * cosf(pitch) * cosf(yaw)
    };

    camera.position = Vector3Add(playerPosition, offset);
    camera.target = playerPosition;
    camera.up = { 0.0f, 1.0f, 0.0f };
}

Camera3D CameraManager::GetCamera3D() const { return camera; }