#include "game_manager.hpp"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {}

GameManager::~GameManager() {}

GameManager* GameManager::getInstance(){
    if (instance == nullptr){
            instance = new GameManager();
    }
    return instance;
}
