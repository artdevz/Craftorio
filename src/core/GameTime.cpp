#include "core/GameTime.hpp"
#include <inttypes.h>

void GameTime::Update(float delta) { realTime += delta * 60.0f; }

int64_t GameTime::GetGameTime() const { return static_cast<int64_t>(realTime * 60.0f); } // 1 segundo (RealTime) = 1 minuto (GameTime)

std::string GameTime::GetTimeString() const {
    int64_t time = GetGameTime();
    int64_t year = (time / 31536000);
    int64_t day = (time / 86400) % 365;
    int64_t hour = (time / 3600) % 24;
    int64_t minute = (time / 60) % 60;

    // char buffer[16];
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%02" PRId64 "/%03" PRId64 " %02" PRId64 ":%02" PRId64 ":%02" PRId64, year + 1, day + 1, hour, minute, time % 60);
    return std::string(buffer);
}