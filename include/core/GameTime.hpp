#pragma once
#include <string>
#include <cstdint>

class GameTime {

public:
    void Update(float delta); // Delta: Tempo real entre frames

    int64_t GetGameTime() const; // Game Time

    std::string GetTimeString() const;

private:
    float realTime = 0.0f; // Real Time

};