#include "survival.hpp"
#include "../../game_elements/player.hpp"
#include "../../core/system.hpp"
#include <cstdio>



Survival::Survival() {
    this->drawer = DrawManager::getInstance();
    this->drawer->initSurvivorTextures();
    auto [x,y] = System::getInstance()->getScreenSizeWH();
    this->player= Player(x* 0.5, y *0.5, 50, 60, 500);
    this->mapTexture= this->drawer->getPlayerTexture();
    this->state= SurvivalState::IN_GAME;
}

Survival::~Survival() {
}
