#pragma once

#include <string>
#include <vector>

#include "screens/Screen.hpp"

struct WorldEntry {
    std::string name;
    std::string path;
};

class WorldSelect : public Screen {

public:
    void Init() override;
    void Update() override;
    void Draw() override;
    
    bool ShouldStartGame() const;
    std::string GetSelectedWorld() const;

private:
    std::vector<WorldEntry> worlds;
    size_t selectedIndex = 0;
    bool startGame = false;

    bool creatingNewWorld = false;
    std::string newWorldNameInput;

    bool CreateNewWorld(const std::string& newWorldName);
    void LoadWorlds();
    bool DeleteWorld(const std::string& world);
};