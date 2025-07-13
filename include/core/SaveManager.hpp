#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "core/GameTime.hpp"
#include "entities/Player.hpp"

/**
 * @brief Gerencia o save do jogo
 * 
 * Centraliza o salvamento e carregamento de saves do jogador
 */

namespace SaveManager {
    bool CreateWorld(const std::string& name, int64_t seed);
    std::vector<std::string> ListWorlds();
    bool DeleteWorld(const std::string& name);

    void SavePlayer(const std::string& worldName, const Player& player);
    void LoadPlayer(const std::string& worldName, Player& player);

    void SaveTime(const std::string& worldName, const GameTime& time);
    void LoadTime(const std::string& worldName, GameTime& time);

    void SaveWorld(const std::string& worldName, const Player& player, const GameTime& time);
    void LoadWorld(const std::string& worldName, Player& player, GameTime& time);
}