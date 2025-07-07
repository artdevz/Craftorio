#include "entities/LivingEntity.hpp"

LivingEntity::LivingEntity(float maxHP) : 
    PhysicsEntity(), health(maxHP), maxHP(maxHP) {}

void LivingEntity::TakeDamage(float amount) {
    health -= amount;
    if (health < 0.0f) {
        health = 0.0f;
        // TO-DO Died()
    }
}

void LivingEntity::Heal(float amount) {
    health += amount;
    if (health > maxHP) health = maxHP;
}

float LivingEntity::GetMaxHP() const { return maxHP; }
float LivingEntity::GetHP() const { return health; }

float LivingEntity::GetMaxMP() const { return maxMP; }
float LivingEntity::GetMP() const { return mana; }