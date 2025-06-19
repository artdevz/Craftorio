#include "world/Structure.hpp"

Structure::Structure() :
    position({0, 0}), texture({}), hitbox({0, 0, 0, 0}), isWalkable(true) {}

Structure::Structure(Vector2 position, const Texture2D &texture, Rectangle hitbox, bool isWalkable) :
    position(position),
    texture(texture),
    hitbox(hitbox),
    isWalkable(isWalkable) {}
    
void Structure::Update() {}

void Structure::Draw(Vector2 playerPosition) const {
    bool playerBehind = 
        playerPosition.y < position.y + baseOffset && 
        playerPosition.y > GetBounds().y &&
        playerPosition.x > position.x &&
        playerPosition.x < position.x + baseOffset;
    DrawTexture(texture, position.x, position.y - texture.height + baseOffset, (Color)(playerBehind? Color{255, 255, 255, 100} : WHITE));
    DrawRectangleLinesEx(GetHitBox(), 1, RED); // DEBUG 
    DrawRectangleLinesEx(GetBounds(), 1, ORANGE); // DEBUG
    DrawCircleV(Vector2{GetBounds().x, GetBounds().y}, 8, YELLOW); // DEBUG
    DrawCircleV(Vector2{position.x + 32, position.y}, 8, GREEN); // DEBUG
}

void Structure::Interact() {}

Vector2 Structure::GetPosition() const { return position; }

Rectangle Structure::GetBounds() const { return { position.x, position.y - texture.height + baseOffset, (float)texture.width, (float)texture.height }; }

Rectangle Structure::GetHitBox() const { return { position.x + hitbox.x, position.y + hitbox.y, hitbox.width, hitbox.height }; }

bool Structure::IsWalkable() const { return isWalkable; }