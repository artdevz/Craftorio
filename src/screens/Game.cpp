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

Game::Game(const SettingsData& settings, const std::string& worldName) : 
    camera(),
    player(nullptr),
    zombie(nullptr),
    hud(nullptr),
    hotbar(),
    inventory(),
    time(),
    gameManager(time),
    settings(settings),
    worldName(worldName) {
        TraceLog(LOG_INFO, "Game criado");
    }

Game::~Game() {
    if (player) {
        SaveManager::SaveWorld(worldName, *player, time);
    }
    //assetManager.UnloadAll(); // Segmantation Fault
}

void Game::Init() {
    TraceLog(LOG_INFO, "Iniciando o Game");
    player = std::make_unique<Player>();
    zombie = std::make_unique<Zombie>();
    hud = std::make_unique<HUD>(*player);
    SaveManager::LoadWorld(worldName, *player, time);

    for (int x = 0; x < 1024; x++) for (int z = 0; z < 12; z++) for (int y = 0; y > -1; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::GRASS );
    }

    blockManager.AddBlockAt( { (float)-30, (float)1, (float)-30 }, BlockType::LEAVES );
    blockManager.AddBlockAt( { (float)-35, (float)2, (float)-35 }, BlockType::LEAVES );

    for (int x = 0; x < 8; x++) for (int z = 0; z < 8; z++) for (int y = -1; y > -2; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::DIRT );
    }

    for (int x = 0; x < 8; x++) for (int z = 0; z < 8; z++) for (int y = -2; y > -6; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::STONE );
    }

    Tree tree;
    tree.Generate(blockManager, 4, 0, 4);

    TraceLog(LOG_INFO, "Game Iniciado");
}

void Game::Update() {
    gameManager.Update();

    if (player) {
        float checkRadius = 5.0f;
        auto nearbyBlocks = blockManager.GetNearbyBlocks(player->GetPosition(), checkRadius);
        player->Update(GetFrameTime(), camera.GetCamera3D(), nearbyBlocks);
        zombie->Update(GetFrameTime(), nearbyBlocks);
        camera.Update(player->GetPosition(), GetFrameTime());
        hud->Update();
        hotbar.Update();
        inventory.Update();
    }
    time.Update(GetFrameTime());
}

void Game::Draw() {
    float currentHourMinute = time.GetCalendar().date.hour + (time.GetCalendar().date.minute / 60.0f);
    
    Color sky = (currentHourMinute >= 6.0f && currentHourMinute <= 18.0f)? BLUE : BLACK;
    ClearBackground(sky);
    
    float dayProgress = (currentHourMinute - 6.0f) / 12.0f;

    float inclination = DEG2RAD * 30.0f;    // Latitude
    float declination;                      // Declinação Sazonal

    switch (time.GetCalendar().environment.season) {
        case Season::SUMMER: declination = inclination; break;
        case Season::WINTER: declination = -inclination; break;
        default:declination = 0.0f; break; // SPRING & AUTUMN
    }
    
    Vector3 origin = player->GetPosition();
    origin.y += 1.8f;
    
    float sunRadius = 300.0f; // TPS
    float sunAzimuth = Lerp(3.0f * PI / 2.0f, PI / 2.0f, dayProgress);
    float sunElevation = sinf(dayProgress * PI) * (PI / 4) + declination;

    Vector3 sunPosition = {
        origin.x + sinf(sunAzimuth) * cosf(sunElevation) * sunRadius,   // Leste-Oeste
        origin.y + sinf(sunElevation) * sunRadius,                      // Declinação (Altura)
        origin.z + cosf(sunAzimuth) * cosf(sunElevation) * sunRadius    // Norte-Sul
    };

    Vector3 sunLightDirection = Vector3Normalize(Vector3Subtract(origin, sunPosition));
    Vector3 moonLightDirection = Vector3Normalize(Vector3Subtract(origin, {-sunPosition.x, -sunPosition.y, -sunPosition.z} ));
    
    BeginMode3D(camera.GetCamera3D());    
    DrawSphereEx(sunPosition, 24.0f, 16, 16, YELLOW);
    DrawSphereEx({-sunPosition.x, -sunPosition.y, -sunPosition.z}, 24.0f, 16, 16, WHITE);
    // Colocar pra RenderDistance
    blockManager.Draw(player->GetPosition(), (float) settings.video.renderDistance);
    player->Draw();
    zombie->Draw();

    // DEBUG
    origin.y -= 1.8f;
    DrawLine3D(origin, { origin.x, origin.y, origin.z + 5.0f }, DARKBLUE);  // +Z (Norte)
    DrawLine3D(origin, { origin.x, origin.y, origin.z - 5.0f }, GRAY);      // -Z (Sul)
    DrawLine3D(origin, { origin.x + 5.0f, origin.y, origin.z }, RED);       // +X (Oeste)
    DrawLine3D(origin, { origin.x - 5.0f, origin.y, origin.z }, MAGENTA);   // -X (Leste)
    DrawLine3D(origin, { origin.x, origin.y + 5.0f, origin.z }, DARKGREEN); // -X (Zênite)
    DrawLine3D(origin, { origin.x, origin.y - 5.0f, origin.z }, DARKBROWN); // -X (Nadir)

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.GetCamera3D().target, camera.GetCamera3D().position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.GetCamera3D().up));
    Vector3 up = camera.GetCamera3D().up;
    Vector3 playerEyePos = { player->GetPosition().x, player->GetPosition().y + 1.8f, player->GetPosition().z };

    DrawLine3D(playerEyePos, Vector3Add(playerEyePos, Vector3Scale(sunLightDirection, 20.0f)), GOLD);
    DrawLine3D(playerEyePos, Vector3Add(playerEyePos, Vector3Scale(moonLightDirection, 20.0f)), LIGHTGRAY);
    DrawLine3D(playerEyePos, Vector3Add(playerEyePos, Vector3Scale(forward, 20.0f)), RED);
    DrawLine3D(playerEyePos, Vector3Add(playerEyePos, Vector3Scale(right, 20.0f)), DARKBLUE);
    DrawLine3D(playerEyePos, Vector3Add(playerEyePos, Vector3Scale(up, 20.0f)), DARKGREEN);
    DrawSphere(playerEyePos, 0.2f, WHITE);
    //

    EndMode3D();

    DrawText("Norte  (+Z)", 10, 500, 16, DARKBLUE);
    DrawText("Sul    (-Z)", 10, 520, 16, GRAY);
    DrawText("Oeste  (+X)", 10, 540, 16, RED);
    DrawText("Leste  (-X)", 10, 560, 16, MAGENTA);
    DrawText("Zênite (+Y)", 10, 580, 16, DARKGREEN);
    DrawText("Nadir  (-Y)", 10, 600, 16, DARKBROWN);

    gameManager.DrawOverlay();
    DrawText("Craftorio Pre-Alpha 1.1", 10, 10, 20, GRAY);
    DrawFPS(1185, 10);

    char coordBuffer[64];
    snprintf(coordBuffer, sizeof(coordBuffer), "Coords: x%d, y%d, z%d", (int)player->GetPosition().x, (int)player->GetPosition().y, (int)player->GetPosition().z);
    DrawText(coordBuffer, 10, 100, 20, GRAY);

    char realtimeBuffer[64];
    snprintf(realtimeBuffer, sizeof(realtimeBuffer), "RealTime: %" PRId64, time.GetGameTime());
    DrawText(realtimeBuffer, 10, 130, 20, GRAY);

    char gameTimeBuffer[128];
    time.FormatDateString(gameTimeBuffer, sizeof(gameTimeBuffer));
    DrawText(gameTimeBuffer, 10, 160, 20, GRAY);

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
    DrawText(seasonBuffer, 10, 190, 20, seasonColor);

    char moonPhaseBuffer[32];
    time.FormatPhaseString(moonPhaseBuffer, sizeof(moonPhaseBuffer));
    DrawText(moonPhaseBuffer, 10, 220, 20, WHITE);
    
    hud->Draw();
    hotbar.Draw();
    inventory.Draw();
}