#pragma once
#include <raylib.h>

class Entity {

public:
    Entity();

    void Init();
    void Update();
    void Draw();

private:
    Vector2 position;

};