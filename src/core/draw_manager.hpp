#ifndef DRAW_MANAGER_HPP // zio pera
#define DRAW_MANAGER_HPP

// includes also "soundmanager.hpp" { <raylib.h> }, "modality.hpp"
#include "system.hpp"
#include <array>
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

        Font fontRegular, fontOutline;
        // font data
        bool fontAvailable;

        // idealScreen WH = render WH
        const Rectangle idealScreen = {0.0f, 0.0f, RENDER_WIDTH, -RENDER_HEIGHT};
        Rectangle actualScreen; // need update() to work
        std::array<RenderTexture2D, 2> renderSet; // render array -> fast frame swap
        unsigned short int currRenderIndex;

        DrawManager();
    public:
        static const int RENDER_WIDTH = 1920, RENDER_HEIGHT = 1080, // for render
            titleFontSize=90, subTitleFontSize=60,
            buttonFontSize=40, textFontSize=30;


        ~DrawManager();
        DrawManager(const DrawManager&) = delete;
        DrawManager& operator=(const DrawManager&) = delete;
        static DrawManager* getInstance();

        // N.B.: every draw calls should refer to render width & height
        void drawRangeBar(int progress, int height);
        void drawText(const char *text, int x, int y, int fontSize, Color col);
        void drawTextSF(const char *text, int x, int y, int fontSize, Color col1, Color col2, Color col3);
        void drawTextSFC(const char *text, int y, int fontSize, Color col1, Color col2, Color col3);
        void drawArrowSF(float x, float y, float width, float height, float thick, bool verse, Color col1, Color col2, Color col3);
        float measureText(const char *text, int fontSize);

        RenderTexture2D* currRender();
        RenderTexture2D* prevRender();
        void switchRender();
        void drawRender();

        void update();

        Texture2D* getPrevRenderTexture();
        void unsetPrevRenderTexture();

        //Textures
        Texture2D playerTexture, kunaiTexture, mapTexture, lobbyBgTexture;

        void initSurvivorTextures(GAME_MAPS= GAME_MAPS::URBAN);
        void destroySurvivorTextures();

        Texture2D* getPlayerTexture();
        Texture2D* getKunaiTexture();
        Texture2D* getLobbyBgTexture();

        GAME_MAPS loaded_map;
        Texture2D* setMapTexture(GAME_MAPS= GAME_MAPS::URBAN);
        Texture2D* getMapTexture();

};


#endif
