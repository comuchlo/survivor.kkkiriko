#include "system.hpp"
#include<utility>
#include <random>
#include <chrono>
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
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds= std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    this->rng.seed(milliseconds);
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
