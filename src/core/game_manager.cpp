#include "game_manager.hpp"
#include "../components/lobby/lobby.hpp"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {
    mode = std::make_unique<Lobby>();
}

GameManager::~GameManager() {
    mode.reset();
}

GameManager* GameManager::getInstance(){
    if (instance == nullptr){
        instance = new GameManager();
    }
    return instance;
}

void GameManager::resetCamera1() {
    camera1 = (Camera2D) {(Vector2) { 0, 0 }, (Vector2) { 0, 0 }, 0.0f, 1.0f };
}
void GameManager::resetCamera2() {
    camera2 = (Camera2D) {(Vector2) { 0, 0 }, (Vector2) { 0, 0 }, 0.0f, 1.0f };
}

float GameManager::getDeltaTime() {
    return deltaTime;
}

void GameManager::update() {
    deltaTime = GetFrameTime();
}
