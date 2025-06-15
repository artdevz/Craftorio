#include <raylib.h>
#include <memory>
#include "screens/Game.hpp"

Game::Game() : 
    camera({ (float)1280 / 2, (float)720 / 2}, { (float)1280 / 2, (float)720 / 2}),
    player(nullptr),
    inventory() {
        TraceLog(LOG_INFO, "Game criado");
    }

Game::~Game() {
    delete player;
}

void Game::Init() {
    TraceLog(LOG_INFO, "Game iniciado");
    player = new Player();
}

void Game::Update() {
    if (player) {
        player->Update();
        camera.Update(player->GetPosition());
        inventory.Update();
    }
    Draw();
}

void Game::Draw() {
    BeginDrawing();
    DrawFPS(10, 10);
    ClearBackground(RAYWHITE);
    if (player) {
        BeginMode2D(camera.GetCamera2D());
        DrawText("Pressione W A S D para movimentar", 50, 50, 16, BLACK);
        player->Draw();
        EndMode2D();
    }
    inventory.Draw();
    EndDrawing();
}

void Game::SetPlayer(Player* player) { this->player = player; }