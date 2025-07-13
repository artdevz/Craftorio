#include "screens/WorldSelect.hpp"

#include <filesystem>

#include <raylib.h>

#include "core/SaveManager.hpp"

void WorldSelect::Init() { 
    LoadWorlds(); 
    startGame = false;
    creatingNewWorld = false;
    newWorldNameInput.clear();
}

void WorldSelect::Update() {
    if (creatingNewWorld) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key == KEY_BACKSPACE && !newWorldNameInput.empty()) newWorldNameInput.pop_back();
            else if ((key >= 32 && key <= 126) && newWorldNameInput.size() < 20) newWorldNameInput.push_back((char) key);
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (CreateNewWorld(newWorldNameInput)) {
                creatingNewWorld = false;
                newWorldNameInput.clear();
                selectedIndex = (int)worlds.size() - 1;
            }
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            creatingNewWorld = false;
            newWorldNameInput.clear();
        }
    }
    else {
        if (IsKeyPressed(KEY_DOWN)) selectedIndex = (selectedIndex + 1) % (int)worlds.size();
        if (IsKeyPressed(KEY_UP)) selectedIndex = (selectedIndex - 1 + (int)worlds.size()) % (int)worlds.size();

        if (IsKeyPressed(KEY_ENTER) && !worlds.empty()) startGame = true;
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (DeleteWorld(worlds[selectedIndex].name)) {
                worlds.erase(worlds.begin() + selectedIndex);
            }
        }

        if (IsKeyPressed(KEY_N)) {
            creatingNewWorld = true;
            newWorldNameInput.clear();
        }
    }
}

void WorldSelect::Draw() {
    ClearBackground(BLACK);

    if (creatingNewWorld) {
        DrawText("Create New World", 100, 100, 30, YELLOW);
        DrawText("Input a name and press ENTER:", 100, 150, 20, WHITE);
        DrawText(newWorldNameInput.c_str(), 100, 180, 30, GREEN);
        DrawText("Press ESC for cancel", 100, 220, 20, GRAY);        
    } 
    else {
        DrawText("Select a World (N for New World)", 100, 100, 24, WHITE);

        if (worlds.empty()) {
            DrawText("Worlds not found. Press N for create.", 100, 150, 20, RED);
        } else {
            for (size_t i = 0; i < worlds.size(); i++) {
                Color color = (i == selectedIndex) ? YELLOW : GRAY;
                DrawText(worlds[i].name.c_str(), 120, 150 + (int)i * 30, 20, color);
            }
        }

        DrawText("ENTER to PLAY", 100, 400, 20, LIGHTGRAY);
    }
}

bool WorldSelect::ShouldStartGame() const { 
    return startGame && !worlds.empty(); 
}

std::string WorldSelect::GetSelectedWorld() const { 
    if (worlds.empty()) return "";
    TraceLog(LOG_DEBUG, "Path do mundo: %s", worlds[selectedIndex].path.c_str());
    return worlds[selectedIndex].name; 
}

bool WorldSelect::CreateNewWorld(const std::string& newWorldName) {
    if (newWorldName.empty()) return false;
    int64_t seed = time(nullptr);

    bool created = SaveManager::CreateWorld(newWorldName, seed);
    if (created) {
        LoadWorlds();
        return true;
    }
    return false;
}

void WorldSelect::LoadWorlds() {
    worlds.clear();
    if (!std::filesystem::exists("saves")) std::filesystem::create_directory("saves");

    for (const auto& entry : std::filesystem::directory_iterator("saves")) {
        if (entry.is_directory()) worlds.push_back({ entry.path().filename().string(), entry.path().string() });
    }

    selectedIndex = 0;
}

bool WorldSelect::DeleteWorld(const std::string& world) {
    if (world.empty()) return false;
    worlds.clear();
    
    for (const auto& entry : std::filesystem::directory_iterator("saves")) {
        if (entry.is_directory()) worlds.push_back({ entry.path().filename().string(), entry.path().string() });
    }
    return SaveManager::DeleteWorld(world);
}