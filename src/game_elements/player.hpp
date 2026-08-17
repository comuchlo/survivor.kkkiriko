#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdint>
#include <raylib.h>
#include <vector>
#include "kunai.hpp"

enum class PlayerActions {
  IDLE= 1,
  RUNNING_RIGHT,
  RUNNING_LEFT,
  THROWING_KUNAI
};

class Player {
    public:
        Player();
        Player(float, float, int16_t, int16_t, int16_t, int16_t= 250, int64_t = 0);

        float x, y;
        int16_t width, height, health;
        double xVel, yVel;
        bool hitten;
        uint8_t hittenFrame, runningFrame, throwingFrame;
        int16_t speed;
        unsigned long long score;
        PlayerActions action;
        uint8_t frameAnimazioneCamminata, fpsAnimazioneCamminata;
        std::vector<Kunai> kunais;
        Texture2D* texture;
};


#endif
