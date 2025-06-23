#include "world/Block.hpp"

Block::Block(Vector3 position, bool walkable, Color color) :
    position(position), walkable(walkable), color(color) {}

void Block::Update() {}

void Block::Draw() const {
    DrawCube(position, 1.0f, 1.0f, 1.0f, color);
    DrawCubeWires(position, 1.0f, 1.0f, 1.0f, DARKGRAY);
}

bool Block::IsWalkable() const { return walkable; }

void Block::Interact() {}

Vector3 Block::GetPosition() const { return position; }

BoundingBox Block::GetBoundingBox() const {
    return {
        { position.x - 0.5f, position.y - 0.5f, position.z - 0.5f },
        { position.x + 0.5f, position.y + 0.5f, position.z + 0.5f }
    };
}