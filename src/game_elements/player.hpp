#include <raylib.h>
#include <vector>
#include "kunai.hpp"


#ifndef PLAYER_HPP
#define PLAYER_HPP

typedef enum {
  IDLE,
  RUNNING_RIGHT,
  RUNNING_LEFT,
  THROWING_KUNAI
} PlayerActions;

typedef struct {
  float x, y;
  int width, height, vita;
  double xVel, yVel;
  bool hitten;
  unsigned short int hittenFrame, runningFrame, throwingFrame;
  unsigned long long score;
  PlayerActions action;
  //Rectangle oldRec;
  Texture2D texture, attackTexture, kunaiTexture;
  std::vector<Kunai> Kunais;
} Player;


#endif
