#pragma once
#include <string>

enum class ToolMaterial {
    WOOD, // Picareta e Machado não poderão ser feitos
    STONE,
    COPPER,
    BRONZE,
    IRON,
    STEEL,
    SILVER,
    GOLDEN,
    PLATINUM,
    TITANIUM,
    DIAMANTIUM
};

struct ToolStats {
    std::string name;
    int durability;
    float efficiency;
    int miningLevel;
};

inline ToolStats GetToolMaterialStats(ToolMaterial material) {
    switch(material) {
        case ToolMaterial::WOOD:        return {"Wood",         128,    2.0f,   0};
        case ToolMaterial::STONE:       return {"Stone",        256,    4.0f,   1};
        case ToolMaterial::COPPER:      return {"Copper",       512,    5.0f,   2};
        case ToolMaterial::BRONZE:      return {"Bronze",       1024,   5.5f,   2};
        case ToolMaterial::IRON:        return {"Iron",         1536,   5.0f,   3};
        case ToolMaterial::STEEL:       return {"Steel",        3072,   7.0f,   3};
        case ToolMaterial::SILVER:      return {"Silver",       2048,   7.5f,   4};
        case ToolMaterial::GOLDEN:      return {"Golden",       1024,   9.0f,   4};
        case ToolMaterial::PLATINUM:    return {"Platinum",     2048,   10.0f,  5};
        case ToolMaterial::TITANIUM:    return {"Titanium",     4096,   12.0f,  6};
        case ToolMaterial::DIAMANTIUM:  return {"Diamantium",   8192,   15.0f,  7};
        default:                        return {"Unknown",      64,     1.0f,   0};
    }
}