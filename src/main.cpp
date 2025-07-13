#include <memory>

#include <raylib.h>

#include "core/WindowManager.hpp"
#include "core/Settings.hpp"

#include "screens/Game.hpp"
#include "screens/MainMenu.hpp"
#include "screens/WorldSelect.hpp"

int main() {
    SetTraceLogLevel(LOG_DEBUG);

    Settings::Load();
    SettingsData& config = Settings::Get();    
    auto window = std::make_unique<WindowManager>(config.video, "Craftorio");
    
    std::unique_ptr<Screen> currentScreen = std::make_unique<MainMenu>();
    currentScreen->Init();

    std::string selectedWorld;

    while (!WindowShouldClose() && !currentScreen->ShouldClose()) {
        BeginDrawing();
        currentScreen->Update();
        currentScreen->Draw();
        EndDrawing();

        if (auto menu = dynamic_cast<MainMenu*>(currentScreen.get())) {
            if (menu->ShouldStartGame()) {
                currentScreen = std::make_unique<WorldSelect>();
                currentScreen->Init();
            }
        }

        if (auto select = dynamic_cast<WorldSelect*>(currentScreen.get())) {
            if (select->ShouldStartGame()) {
                selectedWorld = select->GetSelectedWorld();
                currentScreen = std::make_unique<Game>(config, selectedWorld);
                currentScreen->Init();
            }
        }
    }

    Settings::Save();
    TraceLog(LOG_INFO, "Saindo...");
    CloseWindow();
    return 0;
}