#include "system.hpp"
#include<utility>
#include <raylib.h>

std::pair<int, int> System::getScreenSize(){
    this->screenHeight= GetScreenHeight();
    this->screenWidth= GetScreenWidth();
    return std::make_pair(screenHeight,screenWidth);
}
