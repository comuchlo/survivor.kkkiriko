#include "howtoplay.hpp"
#include <raylib.h>

HowToPlay::HowToPlay(Texture2D* backgroundImage) {
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
    this->game_manager = GameManager::getInstance();
    this->backgroundImage = backgroundImage;

    this->game_manager->resetCamera1();
}

HowToPlay::~HowToPlay() {

}
