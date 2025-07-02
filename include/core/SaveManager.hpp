#pragma once
#include <raylib.h>
#include "entities/Player.hpp"
#include "core/GameTime.hpp"
#include <vector>
#include <string>

namespace SaveManager {
    bool CreateWorld(const std::string& name, int64_t seed);
    std::vector<std::string> ListWorlds();

    void SavePlayer(const std::string& worldName, const Player& player);
    void LoadPlayer(const std::string& worldName, Player& player);

    void SaveTime(const std::string& worldName, const GameTime& time);
    void LoadTime(const std::string& worldName, GameTime& time);

    void SaveWorld(const std::string& worldName, const Player& player, const GameTime& time);
    void LoadWorld(const std::string& worldName, Player& player, GameTime& time);
}