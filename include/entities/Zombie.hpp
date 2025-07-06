#pragma once
#include "entities/Entity.hpp"
#include <memory>
#include <vector>

class Block;

using BlockList = std::vector<std::shared_ptr<Block>>;

class Zombie : public Entity {

public:
    Zombie();

    void Update(float deltaTime) override;
    void Update(float deltaTime, const BlockList& nearbyBlocks);
    void Draw() const override;

    Vector3 GetPosition() const override;
    void SetPosition(Vector3 position) override;

    float GetMaxHP() const;
    float GetHP() const;

    void TakeDamage(float amount);
    void Heal(float amount);

private:
    Vector3 position;
    bool isOnGround;
    float moveSpeed;
    float velocityY;

    float maxHP;
    float hp;

};