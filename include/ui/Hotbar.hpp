#pragma once
#include <array>
#include "items/Item.hpp"

class Hotbar {
    
public:
    Hotbar();

    void Update();
    void Draw();

private:
    std::array<Item, 8> slots;

};