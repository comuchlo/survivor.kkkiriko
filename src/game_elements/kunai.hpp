#ifndef KUNAI_HPP
#define KUNAI_HPP

#include <cstdint>
#include <raylib.h>
// I guess that kunai are now so dependent from the player (for the way that I imagined)
// that they could be incorporated to the class player...

typedef struct {
    // public:
        Rectangle hitBox;
        // float x, y;
        float move;
        float slope;
        // double xVel, yVel;
        double nearest;
        int nearestIndex;
        // short int speed = 500;
        uint16_t damage;
        // Texture2D* texture;

        // time elapsed since the start of the kunai animation period
        float periodElapsedTime;
        // current frame of the kunai
        uint8_t currFrame;

        // time to leave: when kunai exceed this time it should despwan
        float ttl;

        // Kunai();
        // Kunai(float, float, double, double, double, int, int16_t, int16_t);
} Kunai;

#endif
