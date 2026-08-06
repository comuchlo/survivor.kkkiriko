#include "lobbymenu.hpp"
#include <raylib.h>

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


LobbyMenu::LobbyMenu(Texture2D* backgroundImage) {
    this->choice = MenuSelection::TRAINING;
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
    this->backgroundImage = backgroundImage;
}

LobbyMenu::~LobbyMenu() {

}
