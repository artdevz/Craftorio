#include "world/GrassBlock.hpp"

GrassBlock::GrassBlock(Vector3 position) :
    Block(position, false, GREEN) {}

void GrassBlock::Interact() {
    TraceLog(LOG_DEBUG, "GrassBlock: Interagiu");
}