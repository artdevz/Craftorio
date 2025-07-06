#include <raylib.h>
#include <memory>
#include <string>
#include <inttypes.h>
#include <raymath.h>
#include "screens/Game.hpp"
#include "core/Input.hpp"
#include "core/SaveManager.hpp"
#include "world/Aggregator.hpp"
#include "items/ItemAgreggator.hpp"
#include "enums/Season.hpp"
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
    itemManager.SetHotbar(&hotbar);
    zombie = std::make_unique<Zombie>();
    hud = std::make_unique<HUD>(*player);
    SaveManager::LoadWorld(worldName, *player, time);

    for (int x = 0; x < 16; x++) for (int z = 0; z < 16; z++) for (int y = -1; y > -2; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::GRASS );
    }

    for (int x = 0; x < 16; x++) for (int z = 0; z < 16; z++) for (int y = -2; y > -3; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::DIRT );
    }

    for (int x = 0; x < 16; x++) for (int z = 0; z < 16; z++) for (int y = -3; y > -8; y--) {
        blockManager.AddBlockAt( { (float)x, (float)y, (float)z }, BlockType::STONE );
    }

    for (int x = -32; x < 32; x++) for (int z = -32; z < 32; z++) blockManager.AddBlockAt( { (float)x, -1024.0f, (float)z }, BlockType::END );

    Tree tree;
    tree.Generate(blockManager, 12, 0, 12);

    auto testItem = std::make_unique<Axe>(ToolMaterial::IRON, 1);
    itemManager.AddItem(std::make_shared<ItemEntity>(std::move(testItem), Vector3{10, 0, 10}));

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
        itemManager.Update(GetFrameTime(), player->GetPosition());
        hud->Update();
        hotbar.Update();
        inventory.Update();
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector3 origin = player->GetPosition();
            origin.y += 1.8f;
            Vector3 direction = camera.GetForward();
            std::shared_ptr<Item> activeItem = hotbar.GetLeftHandItem();
            blockManager.Interact(GetFrameTime(), origin, direction, 5.0f, activeItem);
        }
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector3 origin = player->GetPosition();
            origin.y += 1.8f;
            Vector3 direction = camera.GetForward();
            std::shared_ptr<Item> activeItem = hotbar.GetRightHandItem();
            blockManager.Interact(GetFrameTime(), origin, direction, 5.0f, activeItem);
        }
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

    Vector3 moonPosition = { 
        origin.x + -sinf(sunAzimuth) * cosf(sunElevation) * sunRadius,   
        origin.y + -sinf(sunElevation) * sunRadius,                      
        origin.z + -cosf(sunAzimuth) * cosf(sunElevation) * sunRadius    
    };
    
    BeginMode3D(camera.GetCamera3D());    

    DrawSphereEx(sunPosition, 24.0f, 16, 16, YELLOW);
    DrawSphereEx(moonPosition, 24.0f, 16, 16, WHITE);
    blockManager.Draw(player->GetPosition(), (float) settings.video.renderDistance);
    itemManager.Draw();
    player->Draw();
    zombie->Draw();

    EndMode3D();

    DrawText("Norte  (+Z)", 10, 500, 16, DARKBLUE);
    DrawText("Sul    (-Z)", 10, 520, 16, GRAY);
    DrawText("Oeste  (+X)", 10, 540, 16, RED);
    DrawText("Leste  (-X)", 10, 560, 16, MAGENTA);
    DrawText("Zênite (+Y)", 10, 580, 16, DARKGREEN);
    DrawText("Nadir  (-Y)", 10, 600, 16, DARKBROWN);

    gameManager.DrawOverlay();
    DrawText("Craftorio Pre-Alpha 1.3", 10, 10, 20, GRAY);
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
    if (camera.IsFirstPerson()) {
        DrawLine(GetScreenWidth()/2 - 10, GetScreenHeight()/2, GetScreenWidth()/2 + 10, GetScreenHeight()/2, BLACK);
        DrawLine(GetScreenWidth()/2, GetScreenHeight()/2 - 10, GetScreenWidth()/2, GetScreenHeight()/2 + 10, BLACK);
    }
    inventory.Draw();
}