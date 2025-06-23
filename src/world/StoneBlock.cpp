#include "world/StoneBlock.hpp"

StoneBlock::StoneBlock(Vector3 position) :
    Block(position, false, GRAY) {}

void StoneBlock::Interact() {
    TraceLog(LOG_DEBUG, "StoneBlock: Interagiu");
}