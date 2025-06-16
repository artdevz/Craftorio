#include "world/tiles/WallTile.hpp"
#include "items/Item.hpp"

WallTile::WallTile(Vector2 position, Texture2D texture) :
    Tile(position, texture) {}

bool WallTile::IsWalkable() const { return false; }

void WallTile::Interact(const Item& tool) {}