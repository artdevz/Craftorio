#include "core/SaveManager.hpp"

#include <filesystem>
#include <fstream>
#include <vector>

#include "../libs/json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace SaveManager {
    const std::string SAVE_ROOT = "saves/";

    bool CreateWorld(const std::string& name, int64_t seed) {
        TraceLog(LOG_INFO, "Criando mundo...");
        std::string path = SAVE_ROOT + name + "/";
        if (fs::exists(path)) {
            TraceLog(LOG_INFO, "Erro: Já existe um mundo com esse nome");
            return false;
        }

        fs::create_directories(path);

        // Meta -> Informações do Mundo
        json meta;
        meta["worldName"] = name;
        meta["createdAt"] = time(nullptr);
        meta["version"] = 1;
        meta["seed"] = seed;
        std::ofstream(path + "meta.json") << meta.dump(4);

        json world;
        world["name"] = name;
        world["seed"] = seed;
        world["difficulty"] = 0;
        world["time"] = 0;
        std::ofstream(path + "world.json") << world.dump(4);

        json player;
        player["position"] = { {"x", 0}, {"y", 0}, {"z", 0} };
        player["hp"] = 100;
        player["mp"] = 50;
        std::ofstream(path + "player.json") << player.dump(4);

        TraceLog(LOG_INFO, "Mundo gerado com sucesso");
        return true;
    }

    std::vector<std::string> ListWorlds() {
        std::vector<std::string> worlds;
        if (!fs::exists(SAVE_ROOT)) return worlds;

        for (const auto& entry : fs::directory_iterator(SAVE_ROOT)) {
            if (entry.is_directory()) {
                std::string metaPath = entry.path().string() + "/meta.json";
                if (fs::exists(metaPath)) worlds.push_back(entry.path().filename().string());
            }
        }
        TraceLog(LOG_INFO, "Listando todos os mundos");
        return worlds;
    }

    bool DeleteWorld(const std::string& name) {
        TraceLog(LOG_INFO, "Deletando mundo...");
        std::string path = SAVE_ROOT + name + "/";
        if (!fs::exists(path)) {
            TraceLog(LOG_INFO, "Erro: Mundo a ser deletado não existe");
            return false;
        }

        fs::remove_all(path);

        TraceLog(LOG_INFO, "Mundo deletado");
        return true;
    }

    void SavePlayer(const std::string& worldName, const Player& player) {
        TraceLog(LOG_INFO, "Salvando jogador...");
        std::string path = SAVE_ROOT + worldName + "/player.json";
        
        json data;
        data["position"]["x"] = player.GetPosition().x;
        data["position"]["y"] = player.GetPosition().y;
        data["position"]["z"] = player.GetPosition().z;
        data["hp"] = player.GetHP();
        data["mp"] = player.GetMP();

        // TO-DO: Inventory, Hotbar ...
        std::ofstream(path) << data.dump(4);
        TraceLog(LOG_INFO, "Jogador salvo.");
    }

    void LoadPlayer(const std::string& worldName, Player& player) {
        TraceLog(LOG_INFO, "Carregando jogador...");
        std::string path = SAVE_ROOT + worldName + "/player.json";
        if (!fs::exists(path)) return;

        json data;
        std::ifstream(path) >> data;

        auto pos = data["position"];
        player.SetPosition({ pos.value("x", 0.0f), pos.value("y", 0.0f), pos.value("z", 0.0f) });
        // player.SetHP(data.value("hp", 100));
        // player.SetMP(data.value("mp", 50));
        TraceLog(LOG_INFO, "Jogador carregado com sucesso.");
    }

    void SaveTime(const std::string& worldName, const GameTime& time) {
        TraceLog(LOG_INFO, "Salvando Tempo...");
        std::string path = SAVE_ROOT + worldName + "/world.json";
        
        json world;
        world["time"] = time.GetGameTime();

        std::ofstream(path) << world.dump(4);
        TraceLog(LOG_INFO, "Tempo salvo com sucesso.");
    }

    void LoadTime(const std::string& worldName, GameTime& time) {
        TraceLog(LOG_INFO, "Carregando Tempo.");
        std::string path = SAVE_ROOT + worldName + "/world.json";
        if (!fs::exists(path)) return;

        json world;
        std::ifstream(path) >> world;

        time.SetGameTime(world.value("time", 0LL));
        TraceLog(LOG_INFO, "Tempo carregado.");
    }

    void SaveWorld(const std::string& worldName, const Player& player, const GameTime& time) {
        TraceLog(LOG_INFO, "Salvando Mundo...");
        TraceLog(LOG_DEBUG, "Nome do Mundo: %s", worldName.c_str());
        SavePlayer(worldName, player);
        SaveTime(worldName, time);
        TraceLog(LOG_INFO, "Mundo salvo com sucesso.");
    }

    void LoadWorld(const std::string& worldName, Player& player, GameTime& time) {
        TraceLog(LOG_INFO, "Carregando Mundo...");
        LoadPlayer(worldName, player);
        LoadTime(worldName, time);
        TraceLog(LOG_INFO, "Mundo carregado.");
    }

};