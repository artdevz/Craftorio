#pragma once

#include "raylib.h"

#include "enums/LeafType.hpp"
#include "world/Block.hpp"

class LeafBlock : public Block {

public:
    LeafBlock(Vector3 position, LeafType leafType);

    void Update() override;
    void Draw() const override;
    bool IsSolid() const override;
    void Interact(float deltaTime, std::shared_ptr<Item> item) override;

private:
    int durability;
    LeafType leafType;

};