#include "core/UIManager.hpp"

#include "raylib.h"

#include "items/ItemAgreggator.hpp"

void UIManager::DrawItem(const Item* item, float x, float y, float size) {
    if (!item) return;

    Color color = GRAY;

    switch(item->GetItemType()) {
        case ItemType::BLOCK: {
            auto wood = dynamic_cast<const WoodItem*>(item);
            if (wood) {
                switch(wood->GetWoodType()) {
                    case WoodType::OAK: color = GetColorForWood(WoodType::OAK); break;
                    case WoodType::SPRUCE: color = GetColorForWood(WoodType::SPRUCE); break;
                    default: color = GRAY; break;
                }
            }
            break;
        }

        case ItemType::TOOL:
            color = DARKGRAY;
            break;

        case ItemType::WEAPON:
            color = RED;
            break;

        default:
            color = GRAY;
            break;
    }

    DrawRectangle(x, y, size, size, color);
}