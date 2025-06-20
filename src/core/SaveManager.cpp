#include "core/SaveManager.hpp"
#include "libs/json.hpp"
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

namespace SaveManager {
    const std::string SAVE_PATH = "save/player.json";

    void SavePlayerPosition(const Vector2& position) {
        std::filesystem::create_directories("save");
        json data;
        data["position"]["x"] = position.x;
        data["position"]["y"] = position.y;

        std::ofstream out(SAVE_PATH);
        if (out.is_open()) out << data.dump(4);
    }

    void LoadPlayerPosition() {
        std::ifstream in(SAVE_PATH);
        if (!in.is_open()) return {0, 0};

        json data;
        in >> data;

        return {
            data["position"]["x"].get<float>(), data["position"]["y"].get<float>()
        };
    }
};