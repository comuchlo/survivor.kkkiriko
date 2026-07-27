#include "game_manager.hpp"

GameManager* GameManager::getInstance(){
    if (instance == nullptr){
            instance = new GameManager();
    }
    return instance;
}