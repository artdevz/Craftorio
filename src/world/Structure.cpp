#include "world/Structure.hpp"

Structure::Structure() :
    position({0, 0}), isWalkable(true) {}

Structure::Structure(Vector2 position, const Texture2D &texture, bool isWalkable) :
    position(position),
    texture(texture),
    isWalkable(isWalkable) {}
    
void Structure::Update() {}

void Structure::Draw() const {
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Structure::Interact() {}

Vector2 Structure::GetPosition() const { return position; }

bool Structure::IsWalkable() const { return isWalkable; }

Rectangle Structure::GetBounds() const { return { position.x, position.y, (float)texture.width, (float)texture.height }; }