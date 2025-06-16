#pragma once
#include <vector>
#include <memory>
#include "world/Tile.hpp"

class TileManager {

public:
    void AddTile(std::shared_ptr<Tile> tile);
    void Update();
    void Draw() const;

    const std::vector<std::shared_ptr<Tile>>& GetTiles() const;

private:
    std::vector<std::shared_ptr<Tile>> tiles;

};