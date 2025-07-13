#pragma once

#include <raylib.h>

class Entity {

public:
    virtual ~Entity() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() const = 0;

    virtual Vector3 GetPosition() const = 0;
    virtual void SetPosition(Vector3 position) = 0;
};