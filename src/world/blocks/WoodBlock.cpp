#include "world/blocks/WoodBlock.hpp"
#include "items/ItemAgreggator.hpp"

WoodBlock::WoodBlock(Vector3 position, WoodType type) :
    Block(position, BlockType::WOOD), durability(60 * 10), woodType(type) {}

void WoodBlock::Update() {}

void WoodBlock::Draw() const {
    Color color;
    switch (woodType) {
        case WoodType::OAK: color = DARKBROWN; break;
        case WoodType::SPRUCE: color = BLACK; break;
        default: color = GRAY; break;
    }
    DrawCube(GetOrigin(), 1.0f, 1.0f, 1.0f, GetColorForBlock(type));
    DrawCubeWires(GetOrigin(), 1.0f, 1.0f, 1.0f, DARKGRAY);
}

bool WoodBlock::IsSolid() const { return true; }

void WoodBlock::Interact(float deltaTime, std::shared_ptr<Item> item) {
    interactionAccumulator += deltaTime;

    float efficiency = 1.0f;

    if (item && item->GetItemType() == ItemType::TOOL) {
        Tool* tool = dynamic_cast<Tool*>(item.get());
        if (tool) efficiency = tool->GetEfficiency();
    }

    while (interactionAccumulator >= (1.0f / 60.0f)) {
        interactionAccumulator -= (1.0f / 60.0f);
        durability -= efficiency;
    }
    if (durability <= 0) type = BlockType::AIR;
}

std::optional<std::unique_ptr<Item>> WoodBlock::GetDrop() const {
    if (type == BlockType::AIR) return std::make_unique<WoodItem>(woodType, 1);
    return std::nullopt;
}