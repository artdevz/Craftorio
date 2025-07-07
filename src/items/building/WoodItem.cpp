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
    switch(woodType) {
        case WoodType::OAK: return "Oak Wood";
        case WoodType::SPRUCE: return "Spruce Wood";
        default: return "Wood";
    }
}