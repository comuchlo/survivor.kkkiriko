#include "training.hpp"
#include "components/traininggame/traininggame.hpp"
#include <raylib.h>

Training::Training() {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    trainingMap = LoadTexture("./textures/dojo.png");

    game_manager = GameManager::getInstance();
    game_manager->initTraining();

    //init training params
    // copy player stat
    playerParams.copy(game_manager->players[0]); // copy default player once

    trainingModality = std::make_unique<TrainingGame>(&trainingMap);
}

Training::~Training() {
    UnloadTexture(trainingMap);
    game_manager->uninitTraining();
}

TrainingModality::TrainingModality() {
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
}
