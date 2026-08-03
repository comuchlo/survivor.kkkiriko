#include "lobby.hpp"

MenuSelection& operator++(MenuSelection& val){
    if (val == MenuSelection::EXIT){
        val = MenuSelection::TRAINING;
    }else{
        val = static_cast<MenuSelection>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

MenuSelection operator++(MenuSelection& val, int)
{
  MenuSelection oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

MenuSelection& operator--(MenuSelection& val){
    if (val == MenuSelection::TRAINING){
        val = MenuSelection::EXIT;
    }else{
        val = static_cast<MenuSelection>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

MenuSelection operator--(MenuSelection& val, int)
{
  MenuSelection oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}


Lobby::Lobby(System *sys) {
    this->choice = MenuSelection::TRAINING;
    this->sys = sys;
    this->drawer = DrawManager::getInstance();
    this->backgroundImage = LoadTexture("./textures/kirikobg2.png");
}

Lobby::~Lobby() {
    UnloadTexture(this->backgroundImage);
}

bool Lobby::shouldExit(){
    return (this->choice == MenuSelection::EXIT);
}
