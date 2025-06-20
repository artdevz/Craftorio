#pragma once
#include <raylib.h>
#include "entities/Player.hpp"
#include "core/GameTime.hpp"

namespace SaveManager {
    void SaveWorld(const Player& player, const GameTime& time);
    void LoadWorld(Player& player, GameTime& time);
}