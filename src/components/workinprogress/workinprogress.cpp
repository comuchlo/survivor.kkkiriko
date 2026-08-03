#include "workinprogress.hpp"

WorkInProgress::WorkInProgress(System *sys) {
    this->sys = sys;
    this->drawer = DrawManager::getInstance();
    this->backgroundImage = LoadTexture("./textures/kirikobg2.png");
}

WorkInProgress::~WorkInProgress() {
    UnloadTexture(this->backgroundImage);
}

bool WorkInProgress::shouldExit(){
    return true;
}
