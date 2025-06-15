#pragma once
#include "core/Cam.hpp"
#include "entities/Player.hpp"
#include "ui/Inventory.hpp"

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

};