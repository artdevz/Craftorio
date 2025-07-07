#include "entities/PhysicsEntity.hpp"
#include "utils/Collision.hpp"
#include <raymath.h>

PhysicsEntity::PhysicsEntity() :
    position({0.0f,0.0f,0.0f}),
    velocity({0.0f,0.0f,0.0f}),
    acceleration({0.0f,GRAVITY,0.0f}),
    onGround(false) {}

void PhysicsEntity::Update(float deltaTime) {
    ApplyGravity(deltaTime);

    velocity = Vector3Add(velocity, Vector3Scale(acceleration, deltaTime));
    position = Vector3Add(position, Vector3Scale(velocity, deltaTime));
}

void PhysicsEntity::Update(float deltaTime, const std::vector<std::shared_ptr<Block>>& nearbyBlocks) {
    ApplyGravity(deltaTime);
    velocity = Vector3Add(velocity, Vector3Scale(acceleration, deltaTime));
    ResolveCollisions(nearbyBlocks, deltaTime);
}

void PhysicsEntity::ApplyGravity(float deltaTime) {
    if (!onGround) acceleration.y = GRAVITY;
    else {
        acceleration.y = 0.0f;
        velocity.y = 0.0f;
    }
}

void PhysicsEntity::ResolveCollisions(const std::vector<std::shared_ptr<Block>>& nearbyBlocks, float deltaTime) {
    onGround = false;
    Vector3 nextPosition = position;
    
    // Y
    nextPosition.y += velocity.y * deltaTime;

    // TO-DO: Colocar pra detectar o HitBox do Player, Zombie, Item...
    BoundingBox boxY = {
        { nextPosition.x - boundingBoxWidth, nextPosition.y, nextPosition.z - boundingBoxWidth },
        { nextPosition.x + boundingBoxWidth, nextPosition.y + boundingBoxHeight, nextPosition.z + boundingBoxWidth }
    };

    bool collidedY = CheckCollision<Block>(nearbyBlocks, [&](const Block& block) {
        return block.IsSolid() && CheckCollisionBoxes(boxY, block.GetBoundingBox());
    });

    if (collidedY) {
        velocity.y = 0.0f;
        onGround = true;
    }
    else position.y = nextPosition.y;
    onGround = collidedY;

    // XZ
    Vector3 nextPositionXZ = position;
    nextPositionXZ.x += velocity.x * deltaTime;
    nextPositionXZ.z += velocity.z * deltaTime;

    BoundingBox boxXZ = {
        { nextPositionXZ.x - boundingBoxWidth, position.y + 0.0001f,            position.z - boundingBoxWidth },
        { nextPositionXZ.x + boundingBoxWidth, position.y + boundingBoxHeight,  position.z + boundingBoxWidth }
    };

    bool collidedXZ = CheckCollision<Block>(nearbyBlocks, [&](const Block& block) {
        return block.IsSolid() && CheckCollisionBoxes(boxXZ, block.GetBoundingBox());
    });

    if (!collidedXZ) {
        position.x = nextPositionXZ.x;
        position.z = nextPositionXZ.z;
    }
}

Vector3 PhysicsEntity::GetPosition() const { return position; }
void PhysicsEntity::SetPosition(Vector3 position) { this->position = position; }