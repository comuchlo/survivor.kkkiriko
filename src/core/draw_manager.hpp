#ifndef DRAW_MANAGER_HPP // zio pera
#define DRAW_MANAGER_HPP

// includes also "soundmanager.hpp" { <raylib.h> }, "modality.hpp"
#include "system.hpp"
#include <raylib.h>

enum class GAME_MAPS {
    NONE=1,
    URBAN=2,
    GRASS=3,
};

class DrawManager {
    private:
        static DrawManager* instance;
        System* sys;

        // idealScreen WH = render WH
        const Rectangle idealScreen = {0.0f, 0.0f, RENDER_WIDTH, -RENDER_HEIGHT};
        Rectangle actualScreen; // need update() to work

        DrawManager();

    public:
        static const int RENDER_WIDTH = 1920, RENDER_HEIGHT = 1080; // for render
        RenderTexture2D render;

        ~DrawManager();
        DrawManager(const DrawManager&) = delete;
        DrawManager& operator=(const DrawManager&) = delete;
        static DrawManager* getInstance();

        // N.B.: every draw calls should refer to render width & height
        void drawRangeBar(int progress, int height);
        void drawTextSF(const char *text, int x, int y, int font, Color col1, Color col2, Color col3);
        void drawArrowSF(float x, float y, float width, float height, float thick, bool verse, Color col1, Color col2, Color col3);
        void drawRender();

        void update();

        //Textures
        Texture2D playerTexture, kunaiTexture, mapTexture;

        void initSurvivorTextures(GAME_MAPS= GAME_MAPS::URBAN);
        void destroySurvivorTextures();

        Texture2D* getPlayerTexture();
        Texture2D* getKunaiTexture();

        GAME_MAPS loaded_map;
        Texture2D* setMapTexture(GAME_MAPS= GAME_MAPS::URBAN);
        Texture2D* getMapTexture();

};


#endif
