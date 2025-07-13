#pragma once

#include <memory>
#include <vector>

#include <raylib.h>

#include "entities/Entity.hpp"
#include "world/Block.hpp"

class PhysicsEntity : public Entity {

public:
    PhysicsEntity();
    virtual ~PhysicsEntity() override = default;

    void Update(float deltaTime) override;
    void Update(float deltaTime, const std::vector<std::shared_ptr<Block>>& nearbyBlocks);

    Vector3 GetPosition() const override;
    void SetPosition(Vector3 position) override;

protected:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    bool onGround = false;

    float boundingBoxWidth = 0.4f;
    float boundingBoxHeight = 1.8f;

    void ApplyGravity(float deltaTime);
    void ResolveCollisions(const std::vector<std::shared_ptr<Block>>& blocks, float deltaTime);

    static constexpr float GRAVITY = -25.0f;

};