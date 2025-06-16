#pragma once
#include "world/Structure.hpp"

class Rock : public Structure {

public:
    Rock(Vector2 position, Texture2D texture);

    void Interact() override;

private:
    int durability = 100;

};