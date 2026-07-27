#include "system.hpp"
#include<utility>
#include <raylib.h>


System* System::getInstance(){
    if (instance == nullptr){
            instance = new System();
    }
    return instance;
}

std::pair<int, int> System::getScreenSize(){
    this->screenHeight= GetScreenHeight();
    this->screenWidth= GetScreenWidth();
    return std::make_pair(screenHeight,screenWidth);
}
