#include "howtoplay.hpp"
#include <raylib.h>

HowToPlay::HowToPlay() {
    game_manager = GameManager::getInstance();
    game_manager->resetCamera(0);
}
