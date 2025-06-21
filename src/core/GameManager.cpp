#include "core/GameManager.hpp"
#include <raylib.h>

GameManager::GameManager(GameTime& gameTime) :
    gameTime(gameTime) {}

void GameManager::Update() {
    UpdateDayNightCycle();
}

void GameManager::UpdateDayNightCycle() {
    auto calendar = gameTime.GetCalendar();
    float hour = calendar.date.hour + calendar.date.minute / 60.0f;

    float transition = 1.0f;            // Duração do Dawn/Dusk 
    float day = 6.0f;                   // Início do Dia
    float night = 18.0f;                // Início da Noite
    float dayTimeOffset = 1.0f;         // Diferença de horas nas estações

    switch (calendar.environment.season) {
        case Season::SPRING:
        case Season::AUTUMN: transition = 0.5f; break;
        case Season::SUMMER: day -= dayTimeOffset; night += dayTimeOffset; transition = 1.5f; break;
        case Season::WINTER: day += 1.5f; night -= 1.5f; transition = 0.5f; break;
        default: transition = 1.0f; break;
    }
      
    float dawn = day - transition;      // Transição Noite->Dia
    float dusk = night + transition;    // Transição Dia->Noite

    if (hour >= night && hour <= dusk) 
        lightIntensity = 1.0f - (hour - night) / transition;   // Dusk
    else if (hour >= dawn && hour < day) 
        lightIntensity = (hour - dawn) / transition;           // Dawn
    else if (hour >= day && hour < night) 
        lightIntensity = 1.0f;                                 // Dia
    else 
        lightIntensity = 0.0f;                                 // Noite

    if (hour < day || hour >= night) {
        float moonFactor = 0.0f;
        switch (calendar.environment.phase) {
            case LunarPhase::NEW_MOON:          moonFactor = 0.00f; break; // 0%
            case LunarPhase::WAXING_CRESCENT:   moonFactor = 0.05f; break; // 1%
            case LunarPhase::FIRST_QUARTER:     moonFactor = 0.10f; break; // 2%
            case LunarPhase::WAXING_GIBBOUS:    moonFactor = 0.30f; break; // 6%
            case LunarPhase::FULL_MOON:         moonFactor = 1.00f; break; // 20%
            case LunarPhase::WANING_GIBBOUS:    moonFactor = 0.30f; break; // 6%
            case LunarPhase::LAST_QUARTER:      moonFactor = 0.10f; break; // 2%
            case LunarPhase::WANING_CRESCENT:   moonFactor = 0.05f; break; // 1%
            default: break;
        }
        lightIntensity += moonFactor * 0.2f;
    }

    lightIntensity = Clamp(lightIntensity, 0.0f, 1.0f);

}

void GameManager::DrawOverlay() {
    unsigned char alpha = static_cast<unsigned char>((1.0f - lightIntensity) * 250);
    Color overlay = { 0, 0, 0, alpha };
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), overlay);
}

float GameManager::Clamp(float value, float min, float max) { return (value < min) ? min : (value > max) ? max : value; }