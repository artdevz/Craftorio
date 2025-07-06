#include "world/blocks/WoodBlock.hpp"

WoodBlock::WoodBlock(Vector3 position, WoodType type) :
    Block(position, BlockType::WOOD), durability(60 * 10), woodType(type) {}

void WoodBlock::Update() {}

void WoodBlock::Draw() const {
    Color color;
    switch (woodType) {
        case WoodType::OAK: color = DARKBROWN; break;
        case WoodType::SPRUCE: color = BLACK; break;
        default: color = GRAY; break;
    }
    DrawCube(GetOrigin(), 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
    DrawCubeWires(GetOrigin(), 1.0f, 1.0f, 1.0f, DARKGRAY);
}

bool WoodBlock::IsSolid() const { return true; }

void WoodBlock::Interact(float deltaTime) {
    interactionAccumulator += deltaTime;

    while (interactionAccumulator >= (1.0f / 60.0f)) {
        interactionAccumulator -= (1.0f / 60.0f);
        durability -= 1.0f;
    }
    if (durability <= 0) type = BlockType::AIR;
}