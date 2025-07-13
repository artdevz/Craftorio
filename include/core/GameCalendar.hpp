#pragma once

#include <cstdint>

#include "enums/LunarPhase.hpp"
#include "enums/Season.hpp"

struct GameDate {
    int64_t solar;      // Ano do Game (64 Dias)
    int64_t lunar;      // Mês do Game (8 Dias)
    int64_t day;        // Dia do Game (24 Horas)
    int64_t hour;       // Hora do Game (60 Minutos)
    int64_t minute;     // Minuto do Game (60 Segundos)
                        // 60 Segundos Ingame = 1 Segundo Real
};

struct GameSeasonalState {
    Season season;      // Estação do Ano (16 Dias)
    LunarPhase phase;   // Fase da Lua (1 - 8 Dias) 
};

struct GameCalendar {
    GameDate date;
    GameSeasonalState environment;    
};
