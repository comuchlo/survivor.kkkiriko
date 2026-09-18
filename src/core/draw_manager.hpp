#ifndef DRAW_MANAGER_HPP // zio pera
#define DRAW_MANAGER_HPP

// includes also "soundmanager.hpp" { <raylib.h> }, "modality.hpp"
#include "system.hpp"
#include <array>
#include <cstdint>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

enum class GameMaps {
    NONE=1,
    URBAN=2,
    GRASS=3,
};

enum class InitializedModality {
    NONE = 0,
    TRAINING,
    SURVIVAL,
    DUEL,
};

typedef struct {
    // (N.B.: kunai is part of the skin of the player)

    // name of the skin (≈ id)
    const char* name;

    // total frame number for each skin-type
    uint8_t idleTotFrame, runTotFrame, attackTotFrame, kunaiTotFrame;

    // specify common-for-all skin-frame width and height
    float width, topHeight, bottomHeight,
    // specify width and height of the kunai
        kunaiWidth, kunaiHeight,
    // specify coords where every frame-skin-type is
        topIdleY, bottomIdleY,
        topRunY, bottomRunY,
        topAttackY,
    // specify coords of kunai
        kunaiY;
} PlayerSkinInfo;

typedef struct {
    PlayerSkinInfo skinInfo;
    Texture2D texture;
} PlayerSkin;

class DrawManager {
    private:
        const char *TEXTURES_FOLDER = "./textures/",
            *PLAYERSKIN_FOLDER = "./textures/playerskins/";
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

        // textures & skins
        std::unordered_map<std::string, PlayerSkin> playerSkins;
        Texture2D mapTexture, lobbyBgTexture;

        GameMaps loaded_map;

        // mark what modality was initialized (avoid check for every get)
        InitializedModality initializedMod = InitializedModality::NONE;

        // load all player skins info (once on init)
        bool loadPlayerSkinsInfo();


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

        PlayerSkin* initSurvivorTextures(GameMaps= GameMaps::URBAN);
        void destroySurvivorTextures();

        PlayerSkin* initTrainingTextures();
        void destroyTrainingTextures();

        // get skin texture / info

        // get player skin info
        std::vector<PlayerSkinInfo> getPlayerSkinsInfo();
        // load player skin based on its name
        PlayerSkin* loadPlayerSkin(const char* skinName);
        // unload all player skins
        void unloadPlayerSkins();

        // useful ? only used in Lobby -> should be a Lobby resources
        Texture2D* getLobbyBgTexture();

        Texture2D* setMapTexture(GameMaps= GameMaps::URBAN);
        Texture2D* getMapTexture();
        GameMaps getGameMap();

};


#endif
