#include "world/blocks/DirtBlock.hpp"

DirtBlock::DirtBlock(Vector3 position, DirtType type) :
    Block(position, BlockType::DIRT), durability(10), dirtType(type) {}

void DirtBlock::Update() {}

void DirtBlock::Draw() const {
    DrawCube(position, 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
}

bool DirtBlock::IsSolid() const { return true; }

void DirtBlock::Interact() {
    durability--;
    if (durability <= 0) type = BlockType::AIR;
}