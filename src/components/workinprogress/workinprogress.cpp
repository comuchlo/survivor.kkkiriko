#include "workinprogress.hpp"

WorkInProgress::WorkInProgress() {
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
    this->backgroundImage = LoadTexture("./textures/kirikobg2.png");
}

WorkInProgress::~WorkInProgress() {
    UnloadTexture(this->backgroundImage);
}
