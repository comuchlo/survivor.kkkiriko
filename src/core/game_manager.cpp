#include "game_manager.hpp"
#include "../components/lobby/lobby.hpp"
#include <raylib.h>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {
    this->mode = std::make_unique<Lobby>();
}

GameManager::~GameManager() {
    this->mode.reset();
}

GameManager* GameManager::getInstance(){
    if (instance == nullptr){
        instance = new GameManager();
    }
    return instance;
}

void GameManager::resetCamera1() {
    this->camera1 = (Camera2D) {(Vector2) { 0, 0 }, (Vector2) { 0, 0 }, 0.0f, 1.0f };
}
void GameManager::resetCamera2() {
    this->camera2 = (Camera2D) {(Vector2) { 0, 0 }, (Vector2) { 0, 0 }, 0.0f, 1.0f };
}

float GameManager::getDeltaTime() {
    return this->deltaTime;
}

void GameManager::update() {
    this->deltaTime = GetFrameTime();
}
