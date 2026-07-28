#include "system.hpp"
#include<utility>
#include <raylib.h>


System* System::getInstance(){
    if (instance == nullptr){
            instance = new System();
    }
    return instance;
}

std::pair<int, int> System::getScreenSizeWH(){
    if(this->screenHeight<0 ||this->screenWidth<0 ){
        this->screenHeight= GetScreenHeight(); // se il diddy blud camnbia muore
        this->screenWidth= GetScreenWidth();
    }
    return std::make_pair(this->screenWidth, this->screenHeight);
}

System::System(){
    this->getScreenSizeWH();
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "Kiriko and the donuts");
    /* ToggleFullscreen(); */
    SetWindowIcon(icon);
}

System::~System(){
    UnloadImage(this->icon);
}
