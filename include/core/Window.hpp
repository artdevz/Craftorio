#pragma once
#include <string>
#include <raylib.h>

class Window {

public:
    static Vector2 resolution;

    Window();
    Window(int width, int height, int fpsLimit, std::string title);
    ~Window();

    void SetResolution(int width, int height);
    // void SetDisplay(Display display);
    void SetFpsLimit(int fpsLimit);

};