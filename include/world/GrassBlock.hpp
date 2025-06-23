#pragma once
#include "world/Block.hpp"

class GrassBlock : public Block {

public:
    GrassBlock(Vector3 position);

    void Interact() override;

private:
    int durability = 10;

};