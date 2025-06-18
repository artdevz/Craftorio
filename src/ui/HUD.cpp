#include <raylib.h>
#include "ui/HUD.hpp"

HUD::HUD() :
    health(100.0f), maxHealth(200.0f) {}

void HUD::Update() {
    if (IsKeyPressed(KEY_J)) {
        health -= 10.0f;
        TraceLog(LOG_DEBUG, "Tomou dano!");
    }
    if (health < 0) health = 0;
    if (IsKeyPressed(KEY_K)) {
        health += 10.0f;
        TraceLog(LOG_DEBUG, "Regenerou!");
    }
    if (health > 200) health = 200;
}

void HUD::Draw() {
    DrawRectangle(50, 50, 200, 30, RED);
    DrawRectangle(50, 50, 200 * (health / maxHealth), 30, GREEN);
}