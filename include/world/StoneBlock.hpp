#pragma once
#include "world/Block.hpp"

class StoneBlock : public Block {

public:
    StoneBlock(Vector3 position);

    void Interact() override;

private:
    int durability = 50;

};