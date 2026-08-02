#include <raylib.h>
#include <vector>
#include "kunai.hpp"


#ifndef PLAYER_HPP
#define PLAYER_HPP

enum class PlayerActions {
  IDLE= 1,
  RUNNING_RIGHT,
  RUNNING_LEFT,
  THROWING_KUNAI
};

class Player {
  float x, y;
  int width, height, vita;
  double xVel, yVel;
  bool hitten;
  unsigned short int hittenFrame, runningFrame, throwingFrame;
  short int speed = 250;
  unsigned long long score;
  PlayerActions action;
  Texture2D texture, attackTexture, kunaiTexture;
  short int frameAnimazioneCamminata = 8, fpsAnimazioneCamminata = 8;
  std::vector<Kunai> Kunais;
};


#endif
