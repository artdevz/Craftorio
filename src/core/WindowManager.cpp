#include <raylib.h>
#include "core/WindowManager.hpp"

Vector2 WindowManager::resolution = { 0, 0 };

WindowManager::WindowManager() {
    this->resolution = { (float)1280, (float)720 };
    InitWindow(1280, 720, "Unnamed Game");
    SetTargetFPS(60);
    SetExitKey(KEY_Q);
}

WindowManager::WindowManager(int width, int height, int fpsLimit, std::string title) {
    this->resolution = { (float)width, (float)height };
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fpsLimit);
    SetExitKey(KEY_Q);
}

WindowManager::~WindowManager() {
    TraceLog(LOG_INFO, "Saindo da Janela");
}

void WindowManager::SetResolution(int width, int height) {
    SetWindowSize(width, height);
    resolution = { (float)width, (float)height };
}

void WindowManager::SetFpsLimit(int fpsLimit) {
    SetTargetFPS(fpsLimit);
    TraceLog(LOG_INFO, "Limite de FPS alterado para: %d", fpsLimit);
}