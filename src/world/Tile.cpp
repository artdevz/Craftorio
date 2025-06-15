#include <raylib.h>
#include "world/Tile.hpp"

Tile::Tile() {}

Tile::Tile(Vector2 position, bool isWalkable, const Texture2D& textureRef) :
    position(position),
    isWalkable(isWalkable),
    texture(textureRef) {}

void Tile::Update() {}

void Tile::Draw() const {
    DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
}

Vector2 Tile::GetPosition() const { return position; }
bool Tile::IsWalkable() const { return isWalkable; }
Structure* Tile::GetStructure() const { return structure; }
bool Tile::HasStructure() const { return structure != nullptr; }

void Tile::SetStructure(Structure* structure) { this->structure = structure; } 