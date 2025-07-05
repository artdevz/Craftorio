#include "world/blocks/StoneBlock.hpp"

StoneBlock::StoneBlock(Vector3 position) :
    Block(position, BlockType::STONE), durability(50) {}

void StoneBlock::Update() {}

void StoneBlock::Draw() const {
    DrawCube(position, 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
}

bool StoneBlock::IsSolid() const { return true; }

void StoneBlock::Interact() {
    TraceLog(LOG_DEBUG, "StoneBlock: Interagiu");
    durability--;
    if (durability <= 0) type = BlockType::AIR;
}