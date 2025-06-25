#pragma once
#include "entities/Player.hpp"

class HUD {
    
public:
    HUD(Player& player);

    void Update();
    void Draw();  
    
private:
    Player& player;

};