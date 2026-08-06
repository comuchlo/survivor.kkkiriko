#include "credits.hpp"
#include <raylib.h>

Credits::Credits(Texture2D* backgroundImage) {
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
    this->game_manager = GameManager::getInstance();
    this->backgroundImage = backgroundImage;

    this->game_manager->resetCamera1();
    this->shiftDown = 0;
    this->endedAutoScrool = false;
}

Credits::~Credits() {

}
