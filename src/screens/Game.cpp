#include <raylib.h>
#include <memory>
#include <string>
#include "screens/Game.hpp"

Game::Game() : 
    camera({ (float)1280 / 2, (float)720 / 2}, { (float)1280 / 2, (float)720 / 2}),
    player(nullptr),
    hotbar(),
    inventory() {
        TraceLog(LOG_INFO, "Game criado");
    }

Game::~Game() {
    delete player;
}

void Game::Init() {
    TraceLog(LOG_INFO, "Game iniciado");
    player = new Player();
    Texture2D grassTexture = LoadTexture("assets/images/tiles/Grass.png");
    for (int y = 0; y < 1024; y += 32) for (int x = 0; x < 1024; x += 32) {
        tiles.push_back(Tile({(float)x, (float)y}, 0, grassTexture));
    }
}

void Game::Update() {
    if (player) {
        player->Update();
        camera.Update(player->GetPosition());
        hotbar.Update();
        inventory.Update();
    }
    Draw();
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (player) {
        BeginMode2D(camera.GetCamera2D());
        for (const auto& tile : tiles) {
            if (CheckCollisionRecs( { tile.GetPosition().x, tile.GetPosition().y, (float)tile.SIZE, (float)tile.SIZE },
                { camera.GetCamera2D().target.x - camera.GetCamera2D().offset.x, camera.GetCamera2D().target.y - camera.GetCamera2D().offset.y, 1280, 720 }
            )) tile.Draw();
        }
        DrawText("Pressione W A S D para movimentar", 50, 50, 16, BLACK);
        player->Draw();
        EndMode2D();
        std::string coords = "Coords: x" + std::to_string((int)player->GetPosition().x) + ", y" + std::to_string((int)player->GetPosition().y);
        DrawText(coords.c_str(), 10, 30, 20, BLACK);
    }
    DrawFPS(10, 10);
    hotbar.Draw();
    inventory.Draw();
    EndDrawing();
}

void Game::SetPlayer(Player* player) { this->player = player; }