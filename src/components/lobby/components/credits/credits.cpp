#include "credits.hpp"
#include <raylib.h>

Credits::Credits(Texture2D* backgroundImage) {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    game_manager = GameManager::getInstance();
    this->backgroundImage = backgroundImage;

    game_manager->resetCamera1();
    endedAutoScrool = false;
    stoppedLastText = false;

    autoscroll_speed = DEF_AUTOSCROLL_SPEED;
}

Credits::~Credits() {

}
