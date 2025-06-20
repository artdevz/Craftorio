#pragma once
#include <unordered_map>
#include <string>
#include <raylib.h>

class AssetManager {

public:
    Texture2D LoadTexture(const std::string& id, const std::string& path);
    Sound LoadSound(const std::string& id, const std::string& path);

    const Texture2D GetTexture(const std::string& id) const;
    Sound GetSound(const std::string& id) const;
    
    void UnloadTextures();
    void UnloadSounds(); 

    void UnloadAll();

private:
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Sound> sounds;

};