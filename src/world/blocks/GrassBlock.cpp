#include "world/blocks/GrassBlock.hpp"

GrassBlock::GrassBlock(Vector3 position) :
    Block(position, BlockType::GRASS), durability(15) {}

void GrassBlock::Update() {}

void GrassBlock::Draw() const {
    DrawCube(position, 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
}

bool GrassBlock::IsSolid() const { return true; }

void GrassBlock::Interact() {
    TraceLog(LOG_DEBUG, "GrassBlock: Interagiu");
    durability--;
    if (durability <= 0) type = BlockType::AIR;
}