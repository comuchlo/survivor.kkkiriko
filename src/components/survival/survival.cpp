#include "survival.hpp"
#include <cstdio>



Survival::Survival() {
    // should use game manager
    this->drawer = DrawManager::getInstance();
    this->game_manager = GameManager::getInstance();
    this->game_manager->initSurvival();
    // this->drawer->initSurvivorTextures();
    // auto [x,y] = System::getInstance()->getScreenSizeWH();
    // this->player= Player(x* 0.5, y *0.5, 50, 60, 500);
    this->mapTexture= this->drawer->getMapTexture();
    // this->state= SurvivalState::IN_GAME;
}

Survival::~Survival() {
    this->game_manager->uninitSurvival();
}
