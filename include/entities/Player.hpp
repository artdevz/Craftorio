#pragma once
#include <raylib.h>
#include <memory>
#include <vector>
#include "entities/LivingEntity.hpp"

class Block;
using BlockList = std::vector<std::shared_ptr<Block>>;

static constexpr float PLAYER_HALF_WIDTH = 0.3f;
static constexpr float PLAYER_HEIGHT = 1.8f;

class Player : public LivingEntity {

public:
    Player();
    ~Player() override = default;

    void Update(float deltaTime) override;
    void Update(float deltaTime, const Camera3D& camera, const BlockList& nearbyBlocks);
    void Draw() const override;

    float GetMoveSpeed() const;

private:
    float moveSpeed;

};