#include <raylib.h>
#include <memory>
#include <string>
#include <inttypes.h>
#include <raymath.h>
#include "screens/Game.hpp"
#include "core/Input.hpp"
#include "core/SaveManager.hpp"
#include "world/Aggregator.hpp"
#include "enums/Season.hpp"

#include "items/ShovelData.hpp"
#include "world/structures/Tree.hpp"

Game::Game() : 
    camera(),
    player(nullptr),
    hotbar(),
    inventory(),
    time(),
    gameManager(time) {
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

    for (int x = -128; x < 8; x++) for (int z = -128; z < 8; z++) for (int y = 0; y > -1; y--) {
        if (x > -4 && z > -4 && (x < 0 || z < 0)) continue;
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::GRASS );
    }

    blockManager.AddBlockAt( { (float)-30, (float)1, (float)-30 }, BlockType::LEAVES );

    for (int x = 0; x < 8; x++) for (int z = 0; z < 8; z++) for (int y = -1; y > -2; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::DIRT );
    }

    for (int x = 0; x < 8; x++) for (int z = 0; z < 8; z++) for (int y = -2; y > -6; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::STONE );
    }

    Tree tree;
    tree.Generate(blockManager, -15, 0, -15);
    tree.Generate(blockManager, 4, 0, 4);

    TraceLog(LOG_INFO, "Game Iniciado");
}

void Game::Update() {
    blockManager.Update();
    gameManager.Update();

    if (player) {
        player->Update(blockManager.GetBlocks());
        camera.Update(player->GetPosition());
        hud.Update();
        hotbar.Update();
        inventory.Update();

        /*
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
        */
    }
    time.Update(GetFrameTime());
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLANK);

    if (player) {
        BeginMode3D(camera.GetCamera3D());

        float maxRenderDistance = 16.0f;
        Vector3 playerPos = player->GetPosition();

        for (const auto& block : blockManager.GetBlocks()) {
            Vector3 blockPos = block->GetPosition();
            float dist = Vector3Distance(blockPos, playerPos);

            if (dist <= maxRenderDistance) block->Draw();
        }

        player->Draw();
        EndMode3D();
    }

    gameManager.DrawOverlay();
    DrawText("Craftorio Pre-Alpha 1.0", 10, 10, 20, GRAY);
    DrawFPS(10, 30);

    char coordBuffer[64];
    snprintf(coordBuffer, sizeof(coordBuffer), "Coords: x%d, y%d, y%d", (int)player->GetPosition().x, (int)player->GetPosition().y, (int)player->GetPosition().z);
    DrawText(coordBuffer, 10, 50, 20, GRAY);

    char realtimeBuffer[64];
    snprintf(realtimeBuffer, sizeof(realtimeBuffer), "RealTime: %" PRId64, time.GetGameTime());
    DrawText(realtimeBuffer, 10, 70, 20, GRAY);

    char gameTimeBuffer[128];
    time.FormatDateString(gameTimeBuffer, sizeof(gameTimeBuffer));
    DrawText(gameTimeBuffer, 10, 90, 20, GRAY);

    Color seasonColor;
    
    switch (time.GetCalendar().environment.season) {
        case Season::SPRING: seasonColor = { 250, 50, 100, 255 }; break;
        case Season::SUMMER: seasonColor = { 20, 170, 0, 255 }; break;
        case Season::AUTUMN: seasonColor = { 255, 165, 0, 255 }; break;
        case Season::WINTER: seasonColor = { 160, 245, 250, 255 }; break;
        default: seasonColor = LIGHTGRAY; break;
    }


    char seasonBuffer[32];
    time.FormatSeasonString(seasonBuffer, sizeof(seasonBuffer));
    DrawText(seasonBuffer, 10, 110, 20, seasonColor);
    
    //hud.Draw();
    hotbar.Draw();
    inventory.Draw();
    
    EndDrawing();
}