#ifndef SYSTEM_HPP
#define SYSTEM_HPP

// includes also <raylib.h>
#include "sound_manager.hpp"
#include "modality.hpp"

#include <random>
#include <raylib.h>

typedef std::ranlux24_base RNG;

enum class DisplayMode {
    RESIZABLE_WINDOW = 1,
    FULLSCREEN = 2,
    BORDERLESS_WINDOW = 3,
};

DisplayMode& operator++(DisplayMode& val);
DisplayMode  operator++(DisplayMode& val, int);

DisplayMode& operator--(DisplayMode& val);
DisplayMode  operator--(DisplayMode& val, int);

class System {
    private:
        static const int DEF_FPS = 60,
            DEF_WIDTH = 960, DEF_HEIGHT = 540, // default res should be 16:9
            MIN_WIDTH = 640, MIN_HEIGHT = 360,
            MIN_FPS = 0, MAX_FPS = 360, DELTA_FPS = 10; // N.B.: 0 fps = uncapped

        // static const int RENDER_WIDTH = 1920, RENDER_HEIGHT = 1080; // for render

        static System* instance;

        bool shutdown, pause, borderlessWindow;
        int fps, currMonitor, setting;
        float screenWidth, screenHeight, monitorWidth, monitorHeight;
        Vector2 mousePos;
        Font font;
        Image icon;

        System();
    public:
        static const int titlefontSize=90, subTitleFontSize=60,
            buttonFontSize=40, textFontSize=30;

        RNG rng;
        SoundManager* soundManager; // only system should acquire soundManager
        int choice;
        ModalityType modalityType;
        // RenderTexture2D render;

        System(const System&) = delete;
        System& operator=(const System&) = delete;
        static System* getInstance();
        ~System();

        Vector2 getScreenSizeWH();
        Vector2 getMonitorSizeWH();
        // Vector2 getRenderSizeWH();
        int getCurrentMonitor();

        void updateScreenSizeWH();
        void updateMonitorSizeWH();
        void updateCurrentMonitor();

        unsigned int getFPS();
        unsigned int getCurrentFPS();
        void incrementFPS();
        void decrementFPS();

        bool isVsyncOn();
        void toggleVsync();

        bool shouldExit();
        void shutDown();

        void setFullScreen();
        void setBorderlessWindow();
        void minimizeWindow();
        void maximizeWindow();
        void resetWindow();
        void resizeWindowByWidth(int width);
        void checkWindowResized();
        DisplayMode getDisplayMode();
        void update();

        void resetVideo();
};

#endif
