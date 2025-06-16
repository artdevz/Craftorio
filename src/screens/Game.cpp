#include <raylib.h>
#include <memory>
#include <string>
#include "screens/Game.hpp"
#include "world/tiles/Aggregator.hpp"

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
    Texture2D stoneTexture = LoadTexture("assets/images/structures/Stone.png");
    Texture2D wallTexture = LoadTexture("assets/images/tiles/Wall.png");
    for (int y = -1024; y < 1024; y += 32) for (int x = -1024; x < 1024; x += 32) {
        auto grassTile = std::make_shared<GrassTile>(Vector2{ (float)x, (float)y }, grassTexture);
        tileManager.AddTile(grassTile);
    }
    auto wallTile = std::make_shared<WallTile>(Vector2{ (float)1200, (float)0 }, wallTexture );
    tileManager.AddTile(wallTile);
    auto rock = std::make_shared<Structure>(Vector2{ (float)256, (float)256 }, stoneTexture, false );
    structureManager.AddStructure(rock);
}

void Game::Update() {
    structureManager.Update();
    if (player) {
        player->Update(structureManager.GetStructures(), tileManager.GetTiles());
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
        for (const auto& tile : tileManager.GetTiles()) {
            if (CheckCollisionRecs( { tile->GetPosition().x, tile->GetPosition().y, (float)Tile::SIZE, (float)Tile::SIZE },
                { camera.GetCamera2D().target.x - camera.GetCamera2D().offset.x, camera.GetCamera2D().target.y - camera.GetCamera2D().offset.y, 1280, 720 }
            )) tile->Draw();
        }
        structureManager.Draw();
        player->Draw();
        DrawText("Pressione W A S D para movimentar", 50, 50, 16, BLACK);
        EndMode2D();
        DrawText(("Coords: x" + std::to_string((int)player->GetPosition().x) +", y" + std::to_string((int)player->GetPosition().y)).c_str(), 10, 30, 20, BLACK);
    }
    DrawFPS(10, 10);
    hotbar.Draw();
    inventory.Draw();
    EndDrawing();
}

void Game::SetPlayer(Player* player) { this->player = player; }