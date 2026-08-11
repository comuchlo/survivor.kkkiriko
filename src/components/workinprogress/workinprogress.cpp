#include "workinprogress.hpp"

WorkInProgress::WorkInProgress() {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    backgroundImage = LoadTexture("./textures/kirikobg2.png");
}

WorkInProgress::~WorkInProgress() {
    UnloadTexture(backgroundImage);
}
