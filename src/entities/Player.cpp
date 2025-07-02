#include "entities/Player.hpp"
#include "core/Input.hpp"
#include "world/Block.hpp"
#include "utils/Collision.hpp"
#include <cmath>
#include <raymath.h>

Player::Player() : 
    position({ 0, 0, 0 }),
    isOnGround(false),
    moveSpeed(5.0f),
    velocityY(0.0f),
    health(100.0f),
    maxHealth(100.0f) {}

void Player::Update(float deltaTime) {}

void Player::Update(float deltaTime, const Camera3D& camera, const BlockList& nearbyBlocks) {
    float sprint = Input::IsRunHeld() ? 1.5f : 1.0f;

    constexpr float gravity = 25.0f; // 25.0f;
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
        { position.x - 0.5f, position.y,                 position.z - 0.5f },
        { position.x + 0.5f, position.y + PLAYER_HEIGHT, position.z + 0.5f }
    };
    DrawBoundingBox(verticalBox, RED);
    // TraceLog(LOG_DEBUG, "Desenhando player");
}

Vector3 Player::GetPosition() const { return position; }
void Player::SetPosition(Vector3 position) { this->position = position; }

bool Player::IsOnGround() const { return isOnGround; }

float Player::GetHealth() const { return health; }
float Player::GetMaxHealth() const { return maxHealth; }

void Player::TakeDamage(float amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Player::Heal(float amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}