#include "core/TileManager.hpp"

void TileManager::AddTile(std::shared_ptr<Tile> tile) {
    tiles.push_back(tile);
}

void TileManager::Update() {
    for (auto& tile : tiles) tile->Update();
}

void TileManager::Draw() const {
    for (const auto& tile : tiles) tile->Draw();
}

const std::vector<std::shared_ptr<Tile>>& TileManager::GetTiles() const { return tiles; }