#include "core/Settings.hpp"
#include <fstream>
#include "../libs/json.hpp"

using json = nlohmann::json;
static const char* SETTINGS_FILE = "assets/config/settings.json";

void Settings::Load() {
    std::ifstream file(SETTINGS_FILE);
    if (!file.is_open()) return;

    json j;
    file >> j;

    auto& a = data.audio;
    if (j.contains("audio")) {
        a.effects = j["audio"].value("effects", 100);
        a.master = j["audio"].value("master", 100);
        a.music = j["audio"].value("music", 100);
        a.mute = j["audio"].value("mute", false);
    }

    auto& c = data.controls;
    if (j.contains("controls")) {
        c.mouseSensitivity = j["controls"].value("mouseSensitivity", 1.0f);
        if (j["controls"].contains("keyBindings")) {
            for (auto& [action, key] : j["controls"]["keyBindings"].items()) c.keyBindings[action] = key;
        } 
    }

    data.language = j.value("language", "en");

    auto& v = data.video;
    if (j.contains("video")) {
        v.display       = j["video"].value("display", 0);
        v.fpsLimit      = j["video"].value("fpsLimit", 144);
        v.width         = j["video"].value("width", 1280);
        v.height        = j["video"].value("height", 720);
        v.fullscreen    = j["video"].value("fullscreen", false);
        v.vSync         = j["video"].value("vSync", false);
        v.graphics      = j["video"].value("graphics", 0);
        v.renderDistance= j["video"].value("renderDistance", 48);
        v.shadows       = j["video"].value("shadows", false);
        v.antiAliasing  = j["video"].value("antiAliasing", false);
    }

}

void Settings::Save() {
    const auto& a = data.audio;
    const auto& c = data.controls;
    const auto& v = data.video;

    json j;
    j["audio"] = {
        {"effects", a.effects},
        {"master", a.master},
        {"music", a.music},
        {"mute", a.mute}
    };

    j["controls"]["mouseSensitivity"] = c.mouseSensitivity;
    j["controls"]["keyBindings"] = json::object();
    for (const auto& [action, key] : c.keyBindings) {
        j["controls"]["keyBindings"][action] = key;
    }

    j["language"] = data.language;

    j["video"] = {
        {"display", v.display},
        {"fpsLimit", v.fpsLimit},
        {"width", v.width},
        {"height", v.height},
        {"fullscreen", v.fullscreen},
        {"vSync", v.vSync},
        {"graphics", v.graphics},
        {"renderDistance", v.renderDistance},
        {"shadows", v.shadows},
        {"antiAliasing", v.antiAliasing}
    };

    std::ofstream file(SETTINGS_FILE);
    file << j.dump(4);
}

SettingsData& Settings::Get() { return data; }