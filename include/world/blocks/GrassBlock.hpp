#pragma once

#include "world/Block.hpp"

class GrassBlock : public Block {

public:
    GrassBlock(Vector3 position);

    void Update() override;
    void Draw() const override;
    bool IsSolid() const override;
    void Interact(float deltaTime, std::shared_ptr<Item> item) override;

private:
    int durability;

};