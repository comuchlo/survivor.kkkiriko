#include "traininggame.hpp"
#include <raylib.h>

TrainingGame::TrainingGame(Texture2D* trainingMap) {
    this->trainingMap = trainingMap;
    game_manager = GameManager::getInstance();
    game_manager->resetCamera1();
}
