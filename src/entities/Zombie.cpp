#include "entities/Zombie.hpp"

#include <cmath>

#include "utils/Collision.hpp"
#include "world/Block.hpp"

Zombie::Zombie() : 
    LivingEntity(200.0f) {
        position = { 8, 1, 10 };
        SetBoundingBox({ { -0.3f, 0.01f, -0.3f }, { 0.3f, 1.8f, 0.3f } });
    }

void Zombie::Update(float deltaTime) {}

void Zombie::Update(float deltaTime, const BlockList& nearbyBlocks) {
    float gravity = 25.0f;
    float jumpStrength = 10.0f;
    float boxYOffset = 0.00001f;

    Vector3 nextPos = position;

    velocityY -= gravity * deltaTime;
    
    nextPos.y += velocityY * deltaTime;

    BoundingBox boxY = {
        { nextPos.x - 0.3f, nextPos.y, nextPos.z - 0.3f },
        { nextPos.x + 0.3f, nextPos.y + 1.8f, nextPos.z + 0.3f }
    };

    bool blockedY = CheckCollision<Block>(nearbyBlocks, [&](const Block& block) {
        return block.IsSolid() && CheckCollisionBoxes(boxY, block.GetBoundingBox());
    });

    if (blockedY) {
        nextPos.y = floor(position.y);
        velocityY = 0;
    }
    isOnGround = blockedY;

    position = nextPos;
}

void Zombie::Draw() const {
    DrawCube(Vector3{position.x, position.y + 0.9f, position.z}, 1.0f, 1.8f, 1.0f, RED);
}

Vector3 Zombie::GetPosition() const { return position; }
void Zombie::SetPosition(Vector3 position) { this->position = position; }

// bool Zombie::IsOnGround() const { return IsOnGround; }

float Zombie::GetMaxHP() const { return maxHP; }

float Zombie::GetHP() const { return hp; }

void Zombie::TakeDamage(float amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Zombie::Heal(float amount) {
    hp += amount;
    if (hp > maxHP) hp = maxHP;
}