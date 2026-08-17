#include "player.hpp"
#include "kunai.hpp"
#include "../core/draw_manager.hpp"
#include <vector>


Player::Player()
    : x(0), y(0), width(0), height(0), health(0),
      xVel(0), yVel(0), speed(250), score(0)
{}


Player::Player(float x, float y, int16_t width, int16_t height, int16_t health, int16_t speed, int64_t score){
    this->x= x;
    this->y= y;
    this->width= width;
    this->height= height;
    this->health= health;
    this->xVel= 0;
    this->yVel= 0;
    this->hitten= false;
    this->hittenFrame=0;
    this->runningFrame=0;
    this->throwingFrame=0;
    this->speed= speed;
    this->score= score;
    this->action= PlayerActions::IDLE;
    this->frameAnimazioneCamminata = 8;
    this->fpsAnimazioneCamminata = 8;
    this->kunais= std::vector<Kunai>();
    this->texture= DrawManager::getInstance()->getPlayerTexture();
}
