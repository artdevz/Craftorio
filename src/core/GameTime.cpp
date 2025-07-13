#include "core/GameTime.hpp"

#include <inttypes.h>

void GameTime::Update(double delta) { realTime += delta; }

int64_t GameTime::GetGameTime() const { return static_cast<int64_t>(realTime * 60.0f); } // 1 segundo (RealTime) = 1 minuto (GameTime)

void GameTime::SetGameTime(int64_t gameTime) { realTime = gameTime / 60.0f; }

GameCalendar GameTime::GetCalendar() const {
    int64_t time = GetGameTime() + 6 * 3600;

    constexpr int64_t TIME_PER_DAY = 86400;
    constexpr int64_t TIME_PER_LUNAR = TIME_PER_DAY * 12;
    constexpr int64_t TIME_PER_SEASON = TIME_PER_LUNAR * 3;
    constexpr int64_t TIME_PER_SOLAR = TIME_PER_SEASON * 4;

    int64_t solar = time / TIME_PER_SOLAR; 
    int64_t lunar = (time / TIME_PER_LUNAR) % 12;
    int64_t day = (time / TIME_PER_DAY) % 12;
    int64_t hour = (time / 3600) % 24;
    int64_t minute = (time / 60) % 60;
    
    Season season = static_cast<Season>((time / TIME_PER_SEASON) % 4);
    LunarPhase phase = static_cast<LunarPhase>(((time - 6*3600) / TIME_PER_DAY) % 8);

    GameDate date = { solar+1, lunar+1, day+1, hour, minute };
    GameSeasonalState env = { season, phase };
    return { date, env };
}

void GameTime::FormatDateString(char* buffer, size_t bufferSize) const {
    GameDate date = GetCalendar().date;
    
    snprintf(buffer, bufferSize, 
        "Solar %" PRId64 ", Lunar %" PRId64 ", Day %02" PRId64 " - %02" PRId64 ":%02" PRId64,
        date.solar, date.lunar, date.day, date.hour, date.minute);
}

void GameTime::FormatSeasonString(char* buffer, size_t bufferSize) const {
    GameSeasonalState env = GetCalendar().environment;

    snprintf(buffer, bufferSize,"%s", ToString(env.season));
}

void GameTime::FormatPhaseString(char* buffer, size_t bufferSize) const {
    GameSeasonalState env = GetCalendar().environment;

    snprintf(buffer, bufferSize,"%s", ToString(env.phase));
}