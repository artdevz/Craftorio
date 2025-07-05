#pragma once
#include "world/Block.hpp"
#include "enums/LeafType.hpp"
#include "raylib.h"

class LeafBlock : public Block {

public:
    LeafBlock(Vector3 position, LeafType leafType);

    void Update() override;
    void Draw() const override;
    bool IsSolid() const override;
    void Interact() override;

private:
    LeafType leafType;

};