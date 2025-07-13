#pragma once

#include <memory>
#include <vector>

#include "core/AssetManager.hpp"
#include "core/BlockManager.hpp"
#include "core/CameraManager.hpp"
#include "core/GameManager.hpp"
#include "core/GameTime.hpp"
#include "core/ItemManager.hpp"
#include "core/Settings.hpp"

#include "screens/Screen.hpp"

#include "entities/Player.hpp"
#include "entities/Zombie.hpp"

#include "ui/Hotbar.hpp"
#include "ui/HUD.hpp"
#include "ui/Inventory.hpp"

class Game : public Screen {

public:
    Game(const SettingsData& settings, const std::string& worldName);
    ~Game();

    void Init() override;
    void Update() override;
    void Draw() override;

private:
    CameraManager camera;
    std::unique_ptr<Player> player;
    std::unique_ptr<Zombie> zombie;
    std::unique_ptr<HUD> hud;
    Hotbar hotbar;
    Inventory inventory;
    GameTime time;
    GameManager gameManager;
    BlockManager blockManager;
    ItemManager itemManager;
    AssetManager assetManager;
    const SettingsData& settings;
    std::string worldName;

};