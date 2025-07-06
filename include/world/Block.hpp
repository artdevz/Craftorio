#pragma once
#include <raylib.h>
#include "enums/BlockType.hpp"
#include "items/Item.hpp"
#include <memory>

class Block {

public:
    Block(Vector3 position, BlockType type) :
        position(position), type(type) {};
    virtual ~Block() = default;

    virtual void Update() = 0;
    virtual void Draw() const = 0;
    virtual bool IsSolid() const = 0;
    virtual void Interact(float deltaTime, std::shared_ptr<Item> item) = 0;

    Vector3 GetPosition() const { return position; };
    Vector3 GetOrigin() const { return {position.x + 0.5f, position.y + 0.5f, position.z + 0.5f}; }

    BoundingBox GetBoundingBox() const {
        return {
            {position.x, position.y, position.z},
            {position.x + 1.0f, position.y + 1.0f, position.z + 1.0f}
        };
    };

    BlockType GetType() const { return type; }

protected:
    Vector3 position;
    BlockType type;
    bool solid;

    float interactionAccumulator = 0.0f;

};