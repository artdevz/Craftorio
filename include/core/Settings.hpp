#pragma once
#include <string>
#include <unordered_map>

struct AudioSettings {
    int effects = 100, master = 100, music = 100;
    bool mute = false;
};

struct ControlsSettings {
    std::unordered_map<std::string, std::string> keyBindings = {
        {"inventory", "I"},
        {"moveDown", "S"},
        {"moveLeft", "A"},
        {"moveRight", "D"},
        {"moveUp", "W"}
    };
    float mouseSensitivity = 1.0f;
};

struct VideoSettings {
    int display = 0;
    int width = 1280, height = 720;
    int fpsLimit = 144;
    bool fpsUnlimited = false;
    bool fullscreen = false;
    bool vSync = false;
    int graphics = 0;
    int renderDistance = 48;
    bool shadows = false;
    bool antiAliasing = false;
};

struct SettingsData {
    AudioSettings audio;
    ControlsSettings controls;
    std::string language = "en";
    VideoSettings video;
};

class Settings {
    
public:
    static void Load();
    static void Save();
    static SettingsData& Get();

private:
    static inline SettingsData data;

};