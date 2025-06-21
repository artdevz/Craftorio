#pragma once
#include "core/GameTime.hpp"

class GameManager {

public:
    explicit GameManager(GameTime& gameTime);

    void Update();
    void DrawOverlay();

    // bool IsRaining() const;
    float GetLightIntensity() const;

private:
    GameTime& gameTime;

    // bool raining;
    float lightIntensity;

    void UpdateDayNightCycle();
    // void UpdateWeather();

    float Clamp(float value, float min, float max);

};