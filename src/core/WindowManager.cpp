#include <raylib.h>
#include "core/WindowManager.hpp"

Vector2 WindowManager::resolution = { 0, 0 };

WindowManager::WindowManager() : 
    WindowManager(1280, 720, 60, "Unnamed Game") {}

WindowManager::WindowManager(int width, int height, int fpsLimit, std::string title) {
    this->resolution = { (float)width, (float)height };
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fpsLimit <= FPS_UNLIMITED ? 2147483647 : fpsLimit); // 2147483647 = Maior Int32
    SetExitKey(KEY_Q);
    //ToggleFullscreen();
}

WindowManager::~WindowManager() {}

Vector2 WindowManager::GetResolution() { return resolution; }

void WindowManager::SetResolution(int width, int height) {
    SetWindowSize(width, height);
    resolution = { (float)width, (float)height };
}

void WindowManager::SetFpsLimit(int fpsLimit) {
    SetTargetFPS(fpsLimit);
    TraceLog(LOG_INFO, "Limite de FPS alterado para: %d", fpsLimit);
}