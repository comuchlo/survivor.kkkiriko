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

        // draw a range bar with params:
        // - progress in a range of [0, 100]
        // - height of the range bar (always horizontally)
        void drawRangeBar(int progress, int height);
        // raylib::DrawText() with DrawManager font
        void drawText(const char *text, int x, int y, int fontSize, Color col);
        // drawText() but decorated
        void drawTextSF(const char *text, int x, int y, int fontSize, Color col1, Color col2, Color col3);
        // drawTextSF() but x-axis-centered based on RENDER_WIDTH
        void drawTextSFC(const char *text, int y, int fontSize, Color col1, Color col2, Color col3);
        // draw an arrow angle-brackets-like ('<' or '>') with params:
        // - verse: true = left , false = right
        void drawArrowSF(float x, float y, float width, float height, float thick, bool verse, Color col1, Color col2, Color col3);
        // drawTextSFC() with drawArrowSF() that contains the text with params:
        // - drawArrow tells whether to actually print the arrows
        // - arrowPadding: distance between the text and a arrow
        // - arrowThickness: the thickness of the arrow
        void drawTextSFCA(const char *text, int y, int fontSize, bool drawArrow, int arrowPadding, float arrowThickness, Color col1, Color col2, Color col3);
        // raylib::MeasureText with DrawManager font
        float measureText(const char *text, int fontSize);

        RenderTexture2D* currRender();
        RenderTexture2D* prevRender();
        void switchRender();
        void drawRender();

        void update();

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
