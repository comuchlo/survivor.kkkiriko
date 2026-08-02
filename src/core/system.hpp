#include <raylib.h>
#include <utility>
#include <random>
#include "sound_manager.hpp"
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

typedef std::ranlux24_base RNG;

class System {
    private:
        static System* instance;
        SoundManager* soundManager= SoundManager::getInstance();
        bool pause;
        int setting;
        int screenWidth=-1, screenHeight=-1;
        Vector2 mousePos;
        Font font;
        Image icon = LoadImage("./textures/temp donut.png");

        System();
    public:
        RNG rng;
        int titlefontSize=90, subTitleFontSize=60, buttonFontSize=40, textFontSize=30;
        int choice;

        System(const System&) = delete;
        System& operator=(const System&) = delete;
        static System* getInstance();
        ~System();

        std::pair<int,int> getScreenSizeWH();


};

#endif
