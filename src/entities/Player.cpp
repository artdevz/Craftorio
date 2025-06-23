#include "entities/Player.hpp"
#include "core/Input.hpp"
#include "world/Block.hpp"
#include "utils/Collision.hpp"
#include <cmath>

Player::Player() : 
    position({ 0, 0, 0 }), isOnGround(false), moveSpeed(5.0f), velocityY(0.0f) {}

void Player::Update(const BlockList& nearbyBlocks) {
    float deltaTime = GetFrameTime();
    float sprint = Input::IsRunHeld() ? 1.5f : 1.0f;

    constexpr float gravity = 25.0f;
    constexpr float jumpStrength = 9.5f;
    constexpr float boxYOffset = 0.00001f;
    
    Vector3 nextPos = position;

    velocityY -= gravity * deltaTime;
    if (Input::IsSpacePressed() && isOnGround) {
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
    Vector3 direction = {0};
    if (Input::IsMoveUpPressed())    direction.z--;
    if (Input::IsMoveLeftPressed())  direction.x--;
    if (Input::IsMoveDownPressed())  direction.z++;
    if (Input::IsMoveRightPressed()) direction.x++;
    
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