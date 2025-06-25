#pragma once
#include <vector>
#include <memory>
#include "screens/Screen.hpp"
#include "core/AssetManager.hpp"
#include "core/CameraManager.hpp"
#include "core/GameManager.hpp"
#include "core/BlockManager.hpp"
#include "core/GameTime.hpp"
#include "entities/Player.hpp"
#include "ui/HUD.hpp"
#include "ui/Hotbar.hpp"
#include "ui/Inventory.hpp"

class Game : public Screen {

public:
    Game();
    ~Game();

    void Init() override;
    void Update() override;
    void Draw() override;

private:
    CameraManager camera;
    std::unique_ptr<Player> player;
    std::unique_ptr<HUD> hud;
    Hotbar hotbar;
    Inventory inventory;
    GameTime time;
    GameManager gameManager;
    BlockManager blockManager;
    AssetManager assetManager;

};