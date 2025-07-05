#include "world/blocks/LeafBlock.hpp"

LeafBlock::LeafBlock(Vector3 position, LeafType type) :
    Block(position, BlockType::LEAVES), leafType(type) {}

void LeafBlock::Update() {}

void LeafBlock::Draw() const {
    Color color;
    switch (leafType) {
        case LeafType::OAK: color = DARKGREEN; break;
        case LeafType::SPRUCE: color = DARKGREEN; break;
        default: color = GRAY; break;
    }
    DrawCube(position, 1.0f, 1.0f, 1.0f, color);
}

bool LeafBlock::IsSolid() const { return false; }

void LeafBlock::Interact() {}