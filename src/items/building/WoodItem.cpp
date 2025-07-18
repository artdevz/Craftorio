#include "items/building/WoodItem.hpp"

#include <raylib.h>

WoodItem::WoodItem(WoodType type, int count) :
    woodType(type) {
        this->count = count;
        switch(type) {
            case WoodType::OAK: name = "Oak Wood"; break;
            case WoodType::SPRUCE: name = "Spruce Wood"; break;
            default: name = "Wood"; break;
        }
    }

void WoodItem::Update() {}

void WoodItem::Draw() const {}

void WoodItem::Interact() {}

const std::string& WoodItem::GetName() const noexcept {
    static const std::string oak = "Oak Wood";
    static const std::string spruce = "Spruce Wood";
    static const std::string defaultWood = "Wood";

    switch(woodType) {
        case WoodType::OAK: return oak;
        case WoodType::SPRUCE: return spruce;
        default: return defaultWood;
    }
}