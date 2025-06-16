#pragma once
#include "world/Tile.hpp"

class WallTile : public Tile {

public:
    WallTile(Vector2 position, Texture2D texture);

    bool IsWalkable() const override;
    void Interact(const Item& tool) override;

};