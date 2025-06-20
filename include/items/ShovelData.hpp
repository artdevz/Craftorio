#pragma once
#include "items/Item.hpp"

class ShovelData : public Item {

public:
    ShovelData();
    ~ShovelData() override;

    void Update() override;
    void Draw() const override;
    void Interact() override;

};