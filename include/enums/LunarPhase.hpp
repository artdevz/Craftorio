#pragma once

enum class LunarPhase { 
    NEW_MOON,
    WAXING_CRESCENT,
    FIRST_QUARTER,
    WAXING_GIBBOUS,
    FULL_MOON,
    WANING_GIBBOUS,
    LAST_QUARTER,
    WANING_CRESCENT 
};

inline const char* ToString(LunarPhase phase) {
    switch (phase) {
        case LunarPhase::NEW_MOON: return "New Moon";               // 🌑
        case LunarPhase::WAXING_CRESCENT: return "Waxing Crescent"; // 🌒
        case LunarPhase::FIRST_QUARTER: return "First Quarter";     // 🌓
        case LunarPhase::WAXING_GIBBOUS: return "Waxing Gibbous";   // 🌔
        case LunarPhase::FULL_MOON: return "Full Moon";             // 🌕
        case LunarPhase::WANING_GIBBOUS: return "Waning Gibbous";   // 🌖
        case LunarPhase::LAST_QUARTER: return "Last Quarter";       // 🌗
        case LunarPhase::WANING_CRESCENT: return "Waning Crescent"; // 🌘
        default: return "🌑 Unknown";
    }
}