#include <memory>
#include <raylib.h>
#include "screens/Game.hpp"
#include "screens/MainMenu.hpp"
#include "core/WindowManager.hpp"
#include "core/Settings.hpp"

int main() {
    SetTraceLogLevel(LOG_DEBUG);

    Settings::Load();
    SettingsData& config = Settings::Get();    
    auto window = std::make_unique<WindowManager>(config.video.width, config.video.height, config.video.fpsLimit, "Craftorio");
    
    std::unique_ptr<Screen> currentScreen = std::make_unique<MainMenu>();
    currentScreen->Init();

    while (!WindowShouldClose() && !currentScreen->ShouldClose()) {
        BeginDrawing();
        currentScreen->Update();
        currentScreen->Draw();
        EndDrawing();

        if (auto menu = dynamic_cast<MainMenu*>(currentScreen.get())) {
            if (menu->ShouldStartGame()) {
                currentScreen = std::make_unique<Game>();
                currentScreen->Init();
            }
        }
    }

    Settings::Save();
    TraceLog(LOG_INFO, "Saindo...");
    CloseWindow();
    return 0;
}