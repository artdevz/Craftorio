#pragma once
#include "world/Block.hpp"

class GrassBlock : public Block {

public:
    GrassBlock(Vector3 position);

    void Update() override;
    void Draw() const override;
    bool IsSolid() const override;
    void Interact() override;

private:
    int durability;

};