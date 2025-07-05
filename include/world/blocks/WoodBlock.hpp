#pragma once
#include "world/Block.hpp"
#include "enums/WoodType.hpp"
#include <raylib.h>

class WoodBlock : public Block {

public:
    WoodBlock(Vector3 position, WoodType woodType);

    void Update() override;
    void Draw() const override;
    bool IsSolid() const override;
    void Interact() override;

private:
    int durability;
    WoodType woodType;

};