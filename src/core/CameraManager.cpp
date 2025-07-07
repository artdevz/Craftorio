#include "core/CameraManager.hpp"
#include "core/Input.hpp"
#include <raymath.h>

#include <cstdio>

CameraManager::CameraManager() : 
    isFirstPerson(true), yaw(0.0f), pitch(0.0f), distanceToPlayer(10.0f) {
    camera.position = { 0.0f, 0.0f, 0.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 70.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor();
}

void CameraManager::Update(Vector3 playerPosition, float deltaTime) { 
    float sensibility = 5.0f;

    // Talvez usar deltaTime pra que seja mais suave em fps baixo
    if (IsKeyDown(KEY_Z)) {
        if (camera.fovy > 5.0f) camera.fovy--;
        sensibility = 0.5f;
    }
    // else camera.fovy++; // Muito louco!
    else if (camera.fovy < 70.0f) {
        camera.fovy+=2.0f;
        sensibility = 5.0f;
    }
    
    if (Input::IsCameraTogglePressed()) isFirstPerson = !isFirstPerson;

    Vector2 mouseDelta = GetMouseDelta();
    yaw -= mouseDelta.x * 0.003f * sensibility;
    pitch -= mouseDelta.y * 0.003f * sensibility;

    pitch = Clamp(pitch, -PI / 2.2f, PI / 2.2f);
    yaw = fmodf(yaw, 2.0f * PI);
    if (yaw < 0.0f) yaw += 2.0f * PI;

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

bool CameraManager::IsFirstPerson() const { return isFirstPerson; }

Vector3 CameraManager::GetForward() const {
    return Vector3Normalize({
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    });
}