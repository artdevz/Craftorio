#pragma once
#include "world/Structure.hpp"

class Grass : public Structure {

public:
    Grass(Vector2 position, Texture2D texture);

    void Interact() override;

private:
    int durability = 0;

};