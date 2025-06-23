#include "core/SaveManager.hpp"
#include "../libs/json.hpp"
#include <fstream>
#include <filesystem>

using json = nlohmann::json;

namespace SaveManager {
    const std::string SAVE_PATH = "save/world.json";

    void SaveWorld(const Player& player, const GameTime& time) {
        std::filesystem::create_directories("save");
        json data;

        data["player"]["position"]["x"] = player.GetPosition().x;
        data["player"]["position"]["y"] = player.GetPosition().y;
        data["player"]["position"]["z"] = player.GetPosition().z;

        data["time"]["gameTime"] = time.GetGameTime();

        // TO-DO: Inventory, Map ...

        std::ofstream file(SAVE_PATH);
        if (file.is_open()) file << data.dump(4);
    }

    void LoadWorld(Player& player, GameTime& time) {
        std::ifstream file(SAVE_PATH);
        if (!file.is_open()) return; // Arquivo inexistente

        file.seekg(0, std::ios::end);
        if (file.tellg() == 0) return; // Arquivo vazio
        file.seekg(0, std::ios::beg);

        json data;
        try { file >> data; }
        catch (json::parse_error& e) { return; }

        if (data.contains("player") && data["player"].contains("position")) {
            auto pos = data["player"]["position"];
            player.SetPosition( { pos.value("x", 0.0f), pos.value("y", 0.0f), pos.value("z", 0.0f) } );
        }

        if (data.contains("time")) {
            time.SetGameTime(data["time"].value("gameTime", 0LL));
        }

        // TO-DO: Inventory, Map ...
    }
};