#include "world/tiles/GrassTile.hpp"
#include "items/Item.hpp"

GrassTile::GrassTile(Vector2 position, Texture2D texture) :
    Tile(position, texture) {}

bool GrassTile::IsWalkable() const { return !structure || structure->IsWalkable(); }

void GrassTile::Interact(const Item& tool) {
    // if tool == Shovel: GrassTile -> PathTile
    if (true) {
        SetTexture(LoadTexture("assets/images/tiles/PathTile.png"));
    }

    // if tool == Hoe: GrassTile -> FarmTile
}