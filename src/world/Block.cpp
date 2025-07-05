// #include "world/Block.hpp"

// Block::Block(Vector3 position, BlockType type) :
//     position(position), type(type) {}

// void Block::Update() {}

// void Block::Draw() const {
//     DrawCube(position, 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
//     DrawCubeWires(position, 1.0f, 1.0f, 1.0f, DARKGRAY);
// }

// bool Block::IsWalkable() const { return ::IsWalkable(type); }

// void Block::Interact() {}

// Vector3 Block::GetPosition() const { return position; }

// BoundingBox Block::GetBoundingBox() const {
//     return {
//         { position.x - 0.5f, position.y - 0.5f, position.z - 0.5f },
//         { position.x + 0.5f, position.y + 0.5f, position.z + 0.5f }
//     };
// }