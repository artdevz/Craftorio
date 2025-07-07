#pragma once
#include "PhysicsEntity.hpp"

class LivingEntity : public PhysicsEntity {

public:
    LivingEntity(float maxHP);
    virtual ~LivingEntity() override = default;

    void TakeDamage(float amount);
    void Heal(float amount);

    float GetMaxHP() const;
    float GetHP() const;

    float GetMaxMP() const;
    float GetMP() const;

protected:
    float maxHP;
    float health;
    float maxMP;
    float mana;

};