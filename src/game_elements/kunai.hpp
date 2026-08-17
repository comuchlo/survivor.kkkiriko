#ifndef KUNAI_HPP
#define KUNAI_HPP

#include <cstdint>
#include <raylib.h>

class Kunai {
    public:
        float x, y;
        double xVel, yVel;
        double nearest;
        int nearestIndex;
        short int speed = 500;
        short int damage= 40;
        Texture2D* texture;

        Kunai();
        Kunai(float, float, double, double, double, int, int16_t, int16_t);
};

#endif
