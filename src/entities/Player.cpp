#include "entities/Player.hpp"
#include "core/Input.hpp"
#include "world/Block.hpp"
#include "utils/Collision.hpp"
#include <cmath>
#include <raymath.h>

Player::Player() : 
    position({ 0, 0, 0 }), isOnGround(false), moveSpeed(5.0f), velocityY(0.0f) {}

void Player::Update(const Camera3D& camera, const BlockList& nearbyBlocks) {
    float deltaTime = GetFrameTime();
    float sprint = Input::IsRunHeld() ? 1.5f : 1.0f;

    constexpr float gravity = 25.0f;
    constexpr float jumpStrength = 9.5f;
    constexpr float boxYOffset = 0.00001f;
    
    Vector3 nextPos = position;

    velocityY -= gravity * deltaTime;
    if (Input::IsJumpPressed() && isOnGround) {
        velocityY = jumpStrength;
        isOnGround = false; 
    }

    nextPos.y += velocityY * deltaTime;

    BoundingBox boxY = {
        { nextPos.x - 0.5f, nextPos.y,                 nextPos.z - 0.5f },
        { nextPos.x + 0.5f, nextPos.y + PLAYER_HEIGHT, nextPos.z + 0.5f }
    };

    bool blockedY = CheckCollision<Block>(nearbyBlocks, [&](const Block& block) {
        return !block.IsWalkable() && CheckCollisionBoxes(boxY, block.GetBoundingBox());
    });

    if (blockedY) {
        nextPos.y = floor(position.y) + 0.5f;
        velocityY = 0;
    }
    isOnGround = blockedY;

    // Horizontal
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    forward.y = 0;

    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, { 0.0f, 1.0f, 0.0f }));

    Vector3 direction = {0};
    if (Input::IsMoveForwardPressed())    direction = Vector3Add(direction, forward);
    if (Input::IsMoveBackwardPressed())  direction = Vector3Subtract(direction, forward);

    if (Input::IsMoveLeftPressed())  direction = Vector3Subtract(direction, right);
    if (Input::IsMoveRightPressed()) direction = Vector3Add(direction, right);
    direction = Vector3Normalize(direction);
    
    Vector3 horizontalPos = nextPos;
    horizontalPos.x += direction.x * moveSpeed * deltaTime * sprint;
    horizontalPos.z += direction.z * moveSpeed * deltaTime * sprint;
    
    BoundingBox boxXZ = {
        { horizontalPos.x - 0.5f, nextPos.y + boxYOffset,    horizontalPos.z - 0.5f },
        { horizontalPos.x + 0.5f, nextPos.y + PLAYER_HEIGHT, horizontalPos.z + 0.5f }
    };

    bool blockedXZ = CheckCollision<Block>(nearbyBlocks, [&](const Block& block) {
        return !block.IsWalkable() && CheckCollisionBoxes(boxXZ, block.GetBoundingBox());
    }); 

    if (!blockedXZ) {
        nextPos.x = horizontalPos.x;
        nextPos.z = horizontalPos.z;
    }
    
    position = nextPos;    
}

void Player::Draw() {
    DrawCube((Vector3){position.x, position.y + 0.9f, position.z}, 1.0f, PLAYER_HEIGHT, 1.0f, BLUE);
    BoundingBox verticalBox = {
        { position.x - 0.5f, position.y,                 position.z - 0.5f },
        { position.x + 0.5f, position.y + PLAYER_HEIGHT, position.z + 0.5f }
    };
    DrawBoundingBox(verticalBox, RED);
    // TraceLog(LOG_DEBUG, "Desenhando player");
}

Vector3 Player::GetPosition() const { return position; }

void Player::SetPosition(Vector3 position) { this->position = position; }

bool Player::IsOnGround() const { return isOnGround; }