#include "entities/Zombie.hpp"

Zombie::Zombie() :
    position({ 10, 1, 10 }),
    isOnGround(false),
    moveSpeed(5.0f),
    velocityY(0.0f),
    maxHP(200.0f),
    hp(200.0f) {}

void Zombie::Update(float deltaTime) {}

void Zombie::Update(float deltaTime, const BlockList& nearbyBlocks) {
    float gravity = 25.0f;
    float jumpStrength = 9.5f;
    float boxYOffset = 0.00001f;

    // TO-DO
}

void Zombie::Draw() {
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