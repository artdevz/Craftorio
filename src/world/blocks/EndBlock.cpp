#include "world/blocks/EndBlock.hpp"

EndBlock::EndBlock(Vector3 position) :
    Block(position, BlockType::END), durability(-1) {}

void EndBlock::Update() {}

void EndBlock::Draw() const {
    DrawCube(GetOrigin(), 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
}

bool EndBlock::IsSolid() const { return true; }

void EndBlock::Interact(float deltaTime, std::shared_ptr<Item> item) {
    TraceLog(LOG_DEBUG, "Impossível");
}