#include "traininggame.hpp"
#include <raylib.h>

TrainingGame::TrainingGame(Texture2D* trainingMap) {
    this->trainingMap = trainingMap;
    this->game_manager = GameManager::getInstance();
    game_manager->cameraFollowPlayer(0);
}

TrainingGame::~TrainingGame() {
}
