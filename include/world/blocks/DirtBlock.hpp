#pragma once

#include <raylib.h>

#include "enums/DirtType.hpp"
#include "world/Block.hpp"

class DirtBlock : public Block {

public:
    DirtBlock(Vector3 position, DirtType dirtType);

    void Update() override;
    void Draw() const override;
    bool IsSolid() const override;
    void Interact(float deltaTime, std::shared_ptr<Item> item) override;

private:
    int durability;
    DirtType dirtType;

};