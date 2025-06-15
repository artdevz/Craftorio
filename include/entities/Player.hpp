#pragma once
#include <raylib.h>

class Player {

public:
    Player();

    void Update();
    void Draw();

    Vector2 GetPosition() const;

private:
    Vector2 position;
    float moveSpeed;

};