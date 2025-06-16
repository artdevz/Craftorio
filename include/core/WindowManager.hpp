#pragma once
#include <string>
#include <raylib.h>

class WindowManager {

public:
    static Vector2 resolution;

    WindowManager();
    WindowManager(int width, int height, int fpsLimit, std::string title);
    ~WindowManager();

    void SetResolution(int width, int height);
    // void SetDisplay(Display display);
    void SetFpsLimit(int fpsLimit);

};