#include "workinprogress.hpp"

WorkInProgress::WorkInProgress() {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    backgroundImage = LoadTexture("./textures/backgrounds/lobby.png");
}

WorkInProgress::~WorkInProgress() {
    UnloadTexture(backgroundImage);
}
