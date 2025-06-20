#pragma once

enum class Season { 
    SPRING,
    SUMMER,
    AUTUMN,
    WINTER 
};

inline const char* ToString(Season season) {
    switch (season) {
        case Season::SPRING: return "Spring"; // 🌸
        case Season::SUMMER: return "Summer"; // 🌞
        case Season::AUTUMN: return "Autumn"; // 🍂
        case Season::WINTER: return "Winter"; // ❄️
        default: return "Unknown"; 
    }
}