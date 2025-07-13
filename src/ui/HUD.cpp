#include "ui/HUD.hpp"

#include <raylib.h>

#include <string>

HUD::HUD(Player& player) :
    player(player) {}

void HUD::Update() {
    if (IsKeyPressed(KEY_J)) {
        player.TakeDamage(10.0f);
    }
    if (IsKeyPressed(KEY_K)) {
        player.Heal(10.0f);
    }
}

void HUD::Draw() {
    float health = player.GetHP();
    float maxHealth = player.GetMaxHP();

    DrawRectangle(10, 35, 60, 60, WHITE);
    DrawRectangle(80, 40, 180, 30, BLANK);
    DrawRectangleLinesEx({80, 40, 180, 30}, 2, DARKGRAY);
    DrawRectangle(80, 40, 180 * (health / maxHealth), 30, RED);

    std::string hpText = "HP " + std::to_string((int)health) + "/" + std::to_string((int)maxHealth);
    DrawText(hpText.c_str(), 125, 48, 16, WHITE);
}