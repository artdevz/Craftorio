#include "world/Structure.hpp"

Structure::Structure() :
    position({0, 0}), texture({}), hitbox({0, 0, 0, 0}), isWalkable(true) {}

Structure::Structure(Vector2 position, const Texture2D &texture, Rectangle hitbox, bool isWalkable) :
    position(position),
    texture(texture),
    hitbox(hitbox),
    isWalkable(isWalkable) {}
    
void Structure::Update() {}

void Structure::Draw() const {
    DrawTexture(texture, position.x, position.y, WHITE);
    //DrawRectangleLinesEx(GetHitBox(), 1, RED); // Hitbox Limite
}

void Structure::Interact() {}

Vector2 Structure::GetPosition() const { return position; }

Rectangle Structure::GetBounds() const { return { position.x, position.y, (float)texture.width, (float)texture.height }; }

Rectangle Structure::GetHitBox() const { return { position.x + hitbox.x, position.y + hitbox.y, hitbox.width, hitbox.height }; }

bool Structure::IsWalkable() const { return isWalkable; }