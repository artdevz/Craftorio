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
    // float jumpStrength = 12.0f;
    PhysicsEntity::Update(deltaTime, nearbyBlocks);
}

void Zombie::Draw() const {
    DrawCube(Vector3{position.x, position.y + 0.9f, position.z}, 1.0f, 1.8f, 1.0f, RED);
}