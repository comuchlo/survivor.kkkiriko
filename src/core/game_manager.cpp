#include "game_manager.hpp"
#include "modality.hpp"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {
    this->mode= new Modality();

}

GameManager::~GameManager() {}

GameManager* GameManager::getInstance(){
    if (instance == nullptr){
            instance = new GameManager();
    }
    return instance;
}
