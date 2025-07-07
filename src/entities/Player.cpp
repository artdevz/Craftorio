#include "entities/Player.hpp"
#include "core/Input.hpp"
#include "world/Block.hpp"
#include "utils/Collision.hpp"
#include <cmath>
#include <raymath.h>

Player::Player() : 
    LivingEntity(100.0f), moveSpeed(5.0f) {}

void Player::Update(float deltaTime) {}

void Player::Update(float deltaTime, const Camera3D& camera, const BlockList& nearbyBlocks) {
    float sprint = Input::IsRunHeld() ? 1.5f : 1.0f;
    float jumpStrength = 12.0f;

    if (Input::IsJumpPressed() && onGround) {
        velocity.y = jumpStrength;
        onGround = false; 
    }

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    forward.y = 0;
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, { 0.0f, 1.0f, 0.0f }));

    Vector3 direction = {0};
    if (Input::IsMoveForwardPressed())    direction = Vector3Add(direction, forward);
    if (Input::IsMoveBackwardPressed())  direction = Vector3Subtract(direction, forward);
    if (Input::IsMoveLeftPressed())  direction = Vector3Subtract(direction, right);
    if (Input::IsMoveRightPressed()) direction = Vector3Add(direction, right);
    direction = Vector3Normalize(direction);
    
    velocity.x = direction.x * moveSpeed * sprint;
    velocity.z = direction.z * moveSpeed * sprint;

    PhysicsEntity::Update(deltaTime, nearbyBlocks);
}

void Player::Draw() const {
    // DrawCube((Vector3){position.x, position.y + 0.9f, position.z}, 1.0f, PLAYER_HEIGHT, 1.0f, BLUE); // Player 1x2x1
    DrawCube(Vector3{position.x + 0.2f, position.y + 0.31f, position.z}, 0.3f, 0.8f, 0.2f, DARKBLUE);
    DrawCube(Vector3{position.x - 0.2f, position.y + 0.31f, position.z}, 0.3f, 0.8f, 0.2f, DARKBLUE);
    DrawCube(Vector3{position.x + 0.2f, position.y, position.z + 0.2f}, 0.3f, 0.3f, 0.4f, DARKBROWN);
    DrawCube(Vector3{position.x - 0.2f, position.y, position.z + 0.2f}, 0.3f, 0.3f, 0.4f, DARKBROWN);
    DrawCube(Vector3{position.x, position.y + 1.0f, position.z}, 0.7f, 0.5f, 0.2f, BLUE);
    DrawCube(Vector3{position.x, position.y + 1.5f, position.z}, 0.7f, 0.7f, 0.7f, YELLOW);
    DrawCube(Vector3{position.x, position.y + 3.0f, position.z}, 0.1f, 0.1f, 0.1f, BLACK);
    DrawCube(Vector3{position.x, position.y + 3.5f, position.z}, 0.05f, 0.05f, 0.05f, BLACK);
    
    BoundingBox verticalBox = {
        { position.x - 0.4f, position.y,                 position.z - 0.4f },
        { position.x + 0.4f, position.y + PLAYER_HEIGHT, position.z + 0.4f }
    };
    DrawBoundingBox(verticalBox, RED);
    // TraceLog(LOG_DEBUG, "Desenhando player");
}

float Player::GetMoveSpeed() const { return moveSpeed; }