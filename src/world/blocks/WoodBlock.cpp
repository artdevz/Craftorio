#include "world/blocks/WoodBlock.hpp"

WoodBlock::WoodBlock(Vector3 position, WoodType type) :
    Block(position, BlockType::WOOD), durability(40), woodType(type) {}

void WoodBlock::Update() {}

void WoodBlock::Draw() const {
    Color color;
    switch (woodType) {
        case WoodType::OAK: color = DARKBROWN; break;
        case WoodType::SPRUCE: color = BLACK; break;
        default: color = GRAY; break;
    }
    DrawCube(position, 1.0f, 1.0f, 1.0f, color);
}

bool WoodBlock::IsSolid() const { return true; }

void WoodBlock::Interact() {}