#pragma once
#include <vector>
#include "core/CameraManager.hpp"
#include "core/StructureManager.hpp"
#include "core/TileManager.hpp"
#include "core/GameTime.hpp"
#include "entities/Player.hpp"
#include "ui/HUD.hpp"
#include "ui/Hotbar.hpp"
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
    CameraManager camera;
    Player* player;
    HUD hud;
    Hotbar hotbar;
    Inventory inventory;
    TileManager tileManager;
    StructureManager structureManager;
    GameTime time;

};