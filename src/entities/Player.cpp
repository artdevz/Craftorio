#include "entities/Player.hpp"
#include "core/Input.hpp"
#include "world/Structure.hpp" // Talvez não precise por ter em Tile.hpp
#include "world/Tile.hpp"
#include "utils/Collision.hpp"

Player::Player() : 
    position({0, 0}), moveSpeed(170.0f) {}

void Player::Update(const StructureList& nearbyStructures, const TileList& nearbyTiles) {
    Vector2 nextPos = position;
    float deltaTime = GetFrameTime();
    float sprint = Input::IsRunHeld() ? 2.0f : 1.0f;

    if (Input::IsMoveUpPressed()) nextPos.y -= moveSpeed * deltaTime * sprint;
    if (Input::IsMoveLeftPressed()) nextPos.x -= moveSpeed * deltaTime * sprint;
    if (Input::IsMoveDownPressed()) nextPos.y += moveSpeed * deltaTime * sprint;
    if (Input::IsMoveRightPressed()) nextPos.x += moveSpeed * deltaTime * sprint;

    bool blockedByStructure = CheckCollision<Structure>(nearbyStructures, [&](const Structure& structure) {
        return !structure.IsWalkable() && CheckCollisionCircleRec(nextPos, 16, structure.GetHitBox());
    });

    bool blockedByTile = CheckCollision<Tile>(nearbyTiles, [&](const Tile& tile) {
        return !tile.IsWalkable() && CheckCollisionCircleRec(nextPos, 16, tile.GetBounds());
    });

    if (!(blockedByStructure || blockedByTile)) position = nextPos;
    else TraceLog(LOG_DEBUG, "BLOQUEADO!");
    
}

void Player::Draw() {
    DrawCircleV(position, 16, GREEN);
    // TraceLog(LOG_DEBUG, "Desenhando player");
}

Vector2 Player::GetPosition() const { return this->position; }