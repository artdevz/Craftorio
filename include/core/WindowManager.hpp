#pragma once

#include <raylib.h>

#include "core/Settings.hpp"

/**
 * @brief Gerencia a janela do jogo
 * 
 * Resolução, FullScreen, Taxa de Atualização e Título
 */

class WindowManager {

public:
    static constexpr int FPS_UNLIMITED = 0;

    WindowManager(const VideoSettings& settings, std::string title);
    ~WindowManager();

    static Vector2 GetResolution();
    static void SetResolution(int width, int height);
    // void SetDisplay(Display display);
    void SetFpsLimit(int fpsLimit);

private:
    static Vector2 resolution;

};