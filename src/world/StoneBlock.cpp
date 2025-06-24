#include "world/StoneBlock.hpp"

StoneBlock::StoneBlock(Vector3 position) :
    Block(position, BlockType::STONE) {}

void StoneBlock::Interact() {
    TraceLog(LOG_DEBUG, "StoneBlock: Interagiu");
}