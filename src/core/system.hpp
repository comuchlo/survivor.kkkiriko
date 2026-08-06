#ifndef SYSTEM_HPP
#define SYSTEM_HPP

// includes also <raylib.h>
#include "sound_manager.hpp"
#include "modality.hpp"

#include <random>
#include <raylib.h>

typedef std::ranlux24_base RNG;

class System {
    private:
        static const int DEF_FPS = 60,
            DEF_WIDTH = 960, DEF_HEIGHT = 540, // default res should be 16:9
            MIN_WIDTH = 640, MIN_HEIGHT = 360,
            RENDER_WIDTH = 1920, RENDER_HEIGHT = 1080; // for render

        static System* instance;

        bool shutdown, pause;
        int fps = 0, currMonitor, setting;
        float screenWidth, screenHeight, monitorWidth, monitorHeight;
        Vector2 mousePos;
        Font font;
        Image icon;

        System();
    public:
        RNG rng;
        SoundManager* soundManager; // only system should acquire soundManager

        static const int titlefontSize=90, subTitleFontSize=60, buttonFontSize=40, textFontSize=30;
        int choice;
        ModalityType modalityType;
        RenderTexture2D render;

        System(const System&) = delete;
        System& operator=(const System&) = delete;
        static System* getInstance();
        ~System();

        Vector2 getScreenSizeWH();
        Vector2 getMonitorSizeWH();
        Vector2 getRenderSizeWH();
        int getCurrentMonitor();

        int getFPS();

        bool shouldExit();
        void shutDown();
};

#endif
