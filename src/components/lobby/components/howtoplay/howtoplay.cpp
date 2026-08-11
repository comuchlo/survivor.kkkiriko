#include "howtoplay.hpp"
#include <raylib.h>

HowToPlay::HowToPlay(Texture2D* backgroundImage) {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    game_manager = GameManager::getInstance();
    this->backgroundImage = backgroundImage;

    game_manager->resetCamera1();
}

HowToPlay::~HowToPlay() {

}
