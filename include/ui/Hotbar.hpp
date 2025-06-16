#pragma once
#include <array>
#include <memory>
#include "items/Item.hpp"

class Hotbar {
    
public:
    Hotbar();

    void Update();
    void Draw();

private:
    std::array<std::shared_ptr<Item>, 8> slots;

};