#pragma once
#include <vector>
#include "core/Cam.hpp"
#include "entities/Player.hpp"
#include "ui/Inventory.hpp"
#include "world/Tile.hpp"

class Game {

public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

    void SetPlayer(Player* player);

private:
    Cam camera;
    Player* player;
    Inventory inventory;
    std::vector<Tile> tiles;

};