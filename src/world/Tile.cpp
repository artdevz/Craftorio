#include "world/Tile.hpp"

Tile::Tile(Vector2 position, const Texture2D& textureRef) :
    position(position), texture(textureRef) {}

void Tile::Update() {}

void Tile::Draw() const {
    DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
    if (structure) structure->Draw();
}

Vector2 Tile::GetPosition() const { return position; }
Rectangle Tile::GetBounds() const { return { position.x, position.y, SIZE, SIZE }; }
Texture2D Tile::GetTexture() const { return texture; }
void Tile::SetTexture(const Texture2D& newTexture) { texture = newTexture; }

Structure* Tile::GetStructure() const { return structure; }
bool Tile::HasStructure() const { return structure != nullptr; }
void Tile::SetStructure(Structure* structure) { this->structure = structure; } 