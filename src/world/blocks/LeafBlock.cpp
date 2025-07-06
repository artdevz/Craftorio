#include "world/blocks/LeafBlock.hpp"

LeafBlock::LeafBlock(Vector3 position, LeafType type) :
    Block(position, BlockType::LEAVES), durability(60 * 0.5f), leafType(type) {}

void LeafBlock::Update() {}

void LeafBlock::Draw() const {
    Color color;
    switch (leafType) {
        case LeafType::OAK: color = DARKGREEN; break;
        case LeafType::SPRUCE: color = DARKGREEN; break;
        default: color = GRAY; break;
    }
    DrawCube(GetOrigin(), 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
    DrawCubeWires(GetOrigin(), 1.0f, 1.0f, 1.0f, DARKGRAY);
}

bool LeafBlock::IsSolid() const { return false; }

void LeafBlock::Interact(float deltaTime) {
    interactionAccumulator += deltaTime;

    while (interactionAccumulator >= (1.0f / 60.0f)) {
        interactionAccumulator -= (1.0f / 60.0f);
        durability -= 1.0f;
    }
    if (durability <= 0) type = BlockType::AIR;
}