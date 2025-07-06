#include "world/blocks/GrassBlock.hpp"

GrassBlock::GrassBlock(Vector3 position) :
    Block(position, BlockType::GRASS), durability(60 * 0.75f) {}

void GrassBlock::Update() {}

void GrassBlock::Draw() const {
    DrawCube(GetOrigin(), 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
    DrawCubeWires(GetOrigin(), 1.0f, 1.0f, 1.0f, DARKGRAY);
}

bool GrassBlock::IsSolid() const { return true; }

void GrassBlock::Interact(float deltaTime, std::shared_ptr<Item> item) {
    interactionAccumulator += deltaTime;

    while (interactionAccumulator >= (1.0f / 60.0f)) {
        interactionAccumulator -= (1.0f / 60.0f);
        durability -= 1.0f;
    }
    if (durability <= 0) type = BlockType::AIR;
}