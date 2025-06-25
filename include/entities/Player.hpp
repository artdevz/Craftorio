#pragma once
#include <raylib.h>
#include <memory>
#include <vector>
#include "entities/Entity.hpp"

class Block; // Forward

using BlockList = std::vector<std::shared_ptr<Block>>;

static constexpr float PLAYER_HEIGHT = 1.8f;

class Player : public Entity {

public:
    Player();

    void Update(float deltaTime) override;
    void Update(float deltaTime, const Camera3D& camera, const BlockList& nearbyBlocks);
    void Draw() override;

    Vector3 GetPosition() const override;
    void SetPosition(Vector3 position) override;

    bool IsOnGround() const;

    float GetHealth() const;
    float GetMaxHealth() const;

    void TakeDamage(float amount);
    void Heal(float aumont);

private:
    Vector3 position;
    bool isOnGround;
    float moveSpeed;
    float velocityY;

    float health;
    float maxHealth;

};