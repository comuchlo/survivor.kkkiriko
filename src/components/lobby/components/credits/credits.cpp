#include "credits.hpp"
#include <raylib.h>

Credits::Credits()  {
    game_manager = GameManager::getInstance();
    game_manager->resetCamera(0);
    endedAutoScrool = false;
    stoppedLastText = false;

    autoscroll_speed = DEF_AUTOSCROLL_SPEED;
}
