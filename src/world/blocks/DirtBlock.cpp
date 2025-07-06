#include "world/blocks/DirtBlock.hpp"

DirtBlock::DirtBlock(Vector3 position, DirtType type) :
    Block(position, BlockType::DIRT), durability(60 * 0.75f), dirtType(type) {}

void DirtBlock::Update() {}

void DirtBlock::Draw() const {
    DrawCube(GetOrigin(), 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
    DrawCubeWires(GetOrigin(), 1.0f, 1.0f, 1.0f, DARKGRAY);
}

bool DirtBlock::IsSolid() const { return true; }

void DirtBlock::Interact(float deltaTime, std::shared_ptr<Item> item) {
    interactionAccumulator += deltaTime;

    while (interactionAccumulator >= (1.0f / 60.0f)) {
        interactionAccumulator -= (1.0f / 60.0f);
        durability -= 1.0f;
    }
    if (durability <= 0) type = BlockType::AIR;
}