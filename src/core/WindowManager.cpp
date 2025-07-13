#include "core/WindowManager.hpp"

Vector2 WindowManager::resolution = { 0, 0 };

WindowManager::WindowManager(const VideoSettings& settings, std::string title) {
    this->resolution = { (float)settings.width, (float)settings.height };
    InitWindow(resolution.x, resolution.y, title.c_str());
    SetTargetFPS(settings.fpsLimit <= FPS_UNLIMITED ? 2147483647 : settings.fpsLimit); // 2147483647 = Maior Int32
    SetExitKey(KEY_Q);
    if (settings.fullscreen) ToggleFullscreen();
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