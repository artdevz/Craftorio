#pragma once
#include "world/Tile.hpp"

class GrassTile : public Tile {

public:
    GrassTile(Vector2 position, Texture2D texture);

    bool IsWalkable() const override;
    void Interact(const Item& tool) override;

};