#include "world/GrassBlock.hpp"

GrassBlock::GrassBlock(Vector3 position) :
    Block(position, BlockType::GRASS) {}

void GrassBlock::Interact() {
    TraceLog(LOG_DEBUG, "GrassBlock: Interagiu");
}