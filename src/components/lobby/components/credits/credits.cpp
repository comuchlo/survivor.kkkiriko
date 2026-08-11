#include "credits.hpp"
#include <raylib.h>

Credits::Credits(Texture2D* backgroundImage) {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    game_manager = GameManager::getInstance();
    this->backgroundImage = backgroundImage;

    game_manager->resetCamera1();
    shiftDown = 0;
    endedAutoScrool = false;
}

Credits::~Credits() {

}
