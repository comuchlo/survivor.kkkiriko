#include "training.hpp"
#include "components/traininggame/traininggame.hpp"
#include <raylib.h>

Training::Training() {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    trainingMap = LoadTexture("./textures/dojo.png");
    trainingModality = std::make_unique<TrainingGame>(&trainingMap);
}

Training::~Training() {
    UnloadTexture(trainingMap);
}

TrainingModality::TrainingModality() {
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
}
