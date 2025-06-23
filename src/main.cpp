#include <memory>
#include <raylib.h>
#include "screens/Game.hpp"
#include "core/WindowManager.hpp"
#include "core/Settings.hpp"

int main() {
    SetTraceLogLevel(LOG_DEBUG);

    Settings::Load();
    SettingsData& config = Settings::Get();    
    auto window = std::make_unique<WindowManager>(config.video.width, config.video.height, config.video.fpsLimit, "Craftorio");
    
    auto game = std::make_unique<Game>();
    game->Init();

    while (!WindowShouldClose()) {
        game->Update();
        game->Draw();
    }

    Settings::Save();
    TraceLog(LOG_INFO, "Saindo...");
    CloseWindow();
    return 0;
}