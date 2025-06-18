#include <raylib.h>
#include <memory>
#include <string>
#include "screens/Game.hpp"
#include "core/Input.hpp"
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
    TraceLog(LOG_INFO, "Iniciando o Game");
    player = new Player();
    Texture2D grassTileTexture = LoadTexture("assets/images/tiles/GrassTile.png");
    Texture2D stoneTexture = LoadTexture("assets/images/structures/Stone.png");
    Texture2D wallTileTexture = LoadTexture("assets/images/tiles/WallTile.png");
    Texture2D grassTexture = LoadTexture("assets/images/structures/Grass.png");
    Texture2D smallTreeTexture = LoadTexture("assets/images/structures/SmallTree.png");
    Texture2D bigTreeTexture = LoadTexture("assets/images/structures/BigTree.png");

    for (int y = -1024; y < 1024; y += Tile::SIZE) for (int x = -1024; x < 1024; x += Tile::SIZE) {
        auto grassTile = std::make_shared<GrassTile>(Vector2{ (float)x, (float)y }, grassTileTexture);
        tileManager.AddTile(grassTile);
    }

    auto wallTile = std::make_shared<WallTile>(Vector2{ (float)1200, (float)0 }, wallTileTexture );
    tileManager.AddTile(wallTile);
    
    auto rock = std::make_shared<Structure>(
        Vector2{ (float)256, (float)256 },
        stoneTexture,
        (Rectangle){ 0, 0, 32, 32},
        false
     );

    auto grass = std::make_shared<Structure>(
        Vector2{ (float)256, (float)128 },
        grassTexture,
        (Rectangle){ 0, 0, 32, 32},
        true
    );
    
    auto smallTree = std::make_shared<Structure>(
        Vector2{ (float)-256, (float)-256},
        smallTreeTexture,
        (Rectangle){ 0, 0, 32, 32},
        false
    );
    
    auto bigTree = std::make_shared<Structure>(
        Vector2{ (float)-512, (float)-256},
        bigTreeTexture,
        (Rectangle){ 0, 0, 32, 32},
        false
    );
    
    structureManager.AddStructure(rock);
    structureManager.AddStructure(grass);
    structureManager.AddStructure(smallTree);
    structureManager.AddStructure(bigTree);
    
    TraceLog(LOG_INFO, "Game Iniciado");
}

void Game::Update() {
    structureManager.Update();

    if (player) {
        player->Update(structureManager.GetStructures(), tileManager.GetTiles());
        camera.Update(player->GetPosition());
        hud.Update();
        hotbar.Update();
        inventory.Update();

        if (Input::IsUseLeftHandPressed()) {
            Vector2 worldMouse = GetScreenToWorld2D(GetMousePosition(), camera.GetCamera2D());

            for (const auto& tile : tileManager.GetTiles()) {
                if (CheckCollisionPointRec(worldMouse, tile->GetBounds())) {
                    // Item dummy;
                    // tile->Interact(dummy);
                    break;
                }
            }
        }
    }
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

        player->Draw();
        structureManager.Draw();
        DrawText("Pressione W A S D para movimentar", 50, 50, 16, BLACK);
        EndMode2D();
        DrawText(("Coords: x" + std::to_string((int)player->GetPosition().x) +", y" + std::to_string((int)player->GetPosition().y)).c_str(), 10, 30, 20, BLACK);
    }

    DrawFPS(10, 10);
    hud.Draw();
    hotbar.Draw();
    inventory.Draw();
    EndDrawing();
}

void Game::SetPlayer(Player* player) { this->player = player; }