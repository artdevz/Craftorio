#pragma once
#include <string>
#include <cstdint>
#include "core/GameCalendar.hpp"

class GameTime {

public:
    void Update(double delta); // Delta: Tempo real entre frames

    int64_t GetGameTime() const; // Game Time
    void SetGameTime(int64_t gameTime);

    GameCalendar GetCalendar() const;

    void FormatDateString(char* buffer, size_t bufferSize) const;
    void FormatSeasonString(char* buffer, size_t bufferSize) const;
    void FormatPhaseString(char* buffer, size_t bufferSize) const;

private:
    double realTime = 0.0f; // Real Time

};