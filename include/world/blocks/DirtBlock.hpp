#pragma once
#include "world/Block.hpp"
#include "enums/DirtType.hpp"
#include <raylib.h>

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