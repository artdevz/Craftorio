#pragma once
#include <string>
#include <raylib.h>

class WindowManager {

public:
    static constexpr int FPS_UNLIMITED = 0;

    WindowManager();
    WindowManager(int width, int height, int fpsLimit, std::string title);
    ~WindowManager();

    static Vector2 GetResolution();
    static void SetResolution(int width, int height);
    // void SetDisplay(Display display);
    void SetFpsLimit(int fpsLimit);

private:
    static Vector2 resolution;

};