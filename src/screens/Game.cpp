#include <raylib.h>
#include <memory>
#include <string>
#include <inttypes.h>
#include "screens/Game.hpp"
#include "core/Input.hpp"
#include "core/SaveManager.hpp"
#include "world/tiles/Aggregator.hpp"
#include "enums/Season.hpp"

#include "items/ShovelData.hpp"

Game::Game() : 
    camera({ (float)1280 / 2, (float)720 / 2}, { (float)1280 / 2, (float)720 / 2}),
    player(nullptr),
    hotbar(),
    inventory(),
    time() {
        TraceLog(LOG_INFO, "Game criado");
    }

Game::~Game() {
    if (player) {
        SaveManager::SaveWorld(*player, time);
    }
    //assetManager.UnloadAll(); // Segmantation Fault
}

void Game::Init() {
    TraceLog(LOG_INFO, "Iniciando o Game");
    player = std::make_unique<Player>();
    SaveManager::LoadWorld(*player, time);

    assetManager.LoadTexture("grassTile", "assets/images/tiles/GrassTile.png");
    assetManager.LoadTexture("wallTile", "assets/images/tiles/WallTile.png");
    assetManager.LoadTexture("stone", "assets/images/structures/Stone.png");
    assetManager.LoadTexture("grass", "assets/images/structures/Grass.png");
    assetManager.LoadTexture("smallTree", "assets/images/structures/SmallTree.png");
    assetManager.LoadTexture("bigTree", "assets/images/structures/BigTree.png");

    auto& grassTileTexture = assetManager.GetTexture("grassTile");
    for (int y = -1024; y < 1024; y += Tile::SIZE) for (int x = -1024; x < 1024; x += Tile::SIZE) {
        auto grassTile = std::make_shared<GrassTile>(Vector2{ (float)x, (float)y }, grassTileTexture);
        tileManager.AddTile(grassTile);
    }

    tileManager.AddTile(std::make_shared<WallTile>(
        Vector2{ 1200.0f, 0.0f }, assetManager.GetTexture("wallTile")));

    structureManager.AddStructure(std::make_shared<Structure>(
        Vector2{ 256.0f, 256.0f }, assetManager.GetTexture("stone"), Rectangle{0, 0, 32, 32}, false));

    structureManager.AddStructure(std::make_shared<Structure>(
        Vector2{ 256.0f, 128.0f }, assetManager.GetTexture("grass"), Rectangle{0, 0, 32, 32}, true));

    structureManager.AddStructure(std::make_shared<Structure>(
        Vector2{ -256.0f, -256.0f }, assetManager.GetTexture("smallTree"), Rectangle{0, 0, 32, 32}, false));

    structureManager.AddStructure(std::make_shared<Structure>(
        Vector2{ -512.0f, -256.0f }, assetManager.GetTexture("bigTree"), Rectangle{0, 0, 32, 32}, false));
    
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
                    static ShovelData shovel;
                    tile->Interact(shovel);
                    break;
                }
            }
        }
    }
    time.Update(GetFrameTime());
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
        structureManager.Draw(player->GetPosition());
        DrawText("Pressione W A S D para movimentar", 50, 50, 16, BLACK);
        EndMode2D();

        char coordBuffer[64];
        snprintf(coordBuffer, sizeof(coordBuffer), "Coords: x%d, y%d", (int)player->GetPosition().x, (int)player->GetPosition().y);
        DrawText(coordBuffer, 10, 30, 20, BLACK);
    }

    DrawFPS(10, 10);

    char realtimeBuffer[64];
    snprintf(realtimeBuffer, sizeof(realtimeBuffer), "RealTime: %" PRId64, time.GetGameTime());
    DrawText(realtimeBuffer, 10, 100, 20, BLACK);

    char gameTimeBuffer[128];
    time.FormatDateString(gameTimeBuffer, sizeof(gameTimeBuffer));
    DrawText(gameTimeBuffer, 10, 130, 20, BLACK);

    Color seasonColor;
    switch (time.GetCalendar().environment.season) {
        case Season::SPRING: seasonColor = PINK; break;
        case Season::SUMMER: seasonColor = GREEN; break;
        case Season::AUTUMN: seasonColor = ORANGE; break;
        case Season::WINTER: seasonColor = LIGHTGRAY; break;
        default: seasonColor = WHITE; break;
    }

    char seasonBuffer[32];
    time.FormatSeasonString(seasonBuffer, sizeof(seasonBuffer));
    DrawText(seasonBuffer, 10, 160, 20, seasonColor);

    hud.Draw();
    hotbar.Draw();
    inventory.Draw();

    EndDrawing();
}