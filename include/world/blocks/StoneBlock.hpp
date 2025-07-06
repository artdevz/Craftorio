#pragma once
#include "world/Block.hpp"

class StoneBlock : public Block {

public:
    StoneBlock(Vector3 position);

    void Update() override;
    void Draw() const override;
    bool IsSolid() const override;
    void Interact(float deltaTime) override;

private:
    int durability;

};