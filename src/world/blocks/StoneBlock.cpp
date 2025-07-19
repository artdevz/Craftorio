#include "world/blocks/StoneBlock.hpp"

StoneBlock::StoneBlock(Vector3 position) :
    Block(position, BlockType::STONE), durability(60 * 30) {}

void StoneBlock::Update() {}

void StoneBlock::Draw() const {
    DrawCube(GetOrigin(), 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
    if (hovered) DrawCubeWires(GetOrigin(), 1.0f, 1.0f, 1.0f, DARKGRAY);
}

bool StoneBlock::IsSolid() const { return true; }

void StoneBlock::Interact(float deltaTime, std::shared_ptr<Item> item) {
    interactionAccumulator += deltaTime;

    while (interactionAccumulator >= (1.0f / 60.0f)) {
        interactionAccumulator -= (1.0f / 60.0f);
        durability -= 1.0f;
    }
    if (durability <= 0) type = BlockType::AIR;
}