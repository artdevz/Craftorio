#pragma once
#include <raylib.h>
#include <memory>
#include <vector>

class Structure; // Forward
class Tile;

using StructureList = std::vector<std::shared_ptr<Structure>>; // Futuramente colocar um Callback pra função canMove()
using TileList = std::vector<std::shared_ptr<Tile>>;

class Player {

public:
    Player();

    void Update(const StructureList& nearbyStructures, const TileList& nearbyTiles);
    void Draw();

    Vector2 GetPosition() const;

private:
    Vector2 position;
    float moveSpeed;

};