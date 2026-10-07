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
    std::string name;

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


enum class TypeEnemy {
  DONUT = 0,
  KING_DONUT = 1,
  CHAD_DONUT = 2,
};

typedef struct {
    // name of the skin (≈ id)
    std::string name;

    // type of the enemy
    TypeEnemy type;

    // specify common-for-all skin-frame width and height
    float width, height;
} EnemySkinInfo;

typedef struct {
    EnemySkinInfo skinInfo;
    Texture2D texture;
} EnemySkin;

class DrawManager {
    public:
        static constexpr int RENDER_WIDTH = 1920, RENDER_HEIGHT = 1080, // for render
            titleFontSize=90, subTitleFontSize=60,
            buttonFontSize=40, textFontSize=30;

        // EnemyType into const char*
        static const std::array<const std::string, (int)TypeEnemy::CHAD_DONUT+1> enemyTypeStr;

        ~DrawManager();
        DrawManager(const DrawManager&) = delete;
        DrawManager& operator=(const DrawManager&) = delete;
        static DrawManager* getInstance();

        // N.B.: every draw calls should refer to render width & height

        // draw a range bar with params:
        // - progress in a range of [0.0f, 1.0f]
        // - height of the range bar (always horizontally)
        void drawRangeBar(float progress, int height);
        // draw a range bar with params:
        // - progress in a range of [0.0f, 1.0f]
        // - height of the range bar (always horizontally)
        // - displayedValue: value to be displayed at the left of the range bar
        void drawRangeBarEx(float progress, int height, float displayedValue);
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

        void initSurvivorTextures(GameMaps map, PlayerSkin** playerSkin, std::array<EnemySkin*, enemyTypeStr.size()>* enemiesSkin);
        void destroySurvivorTextures();

        void initTrainingTextures(PlayerSkin** playerSkin, std::array<EnemySkin*, enemyTypeStr.size()>* enemiesSkin);
        void destroyTrainingTextures();

        // get skin texture / info

        // get player skin info
        std::vector<PlayerSkinInfo> getPlayerSkinsInfo();
        // load player skin based on its name
        PlayerSkin* loadPlayerSkin(std::string skinName);
        // unload all player skins
        void unloadPlayerSkins();

        // get enemy skin info
        std::array<std::vector<EnemySkinInfo>, DrawManager::enemyTypeStr.size()> getEnemySkinsInfo();
        // load enemy skin based on its name
        EnemySkin* loadEnemySkin(int numberType, std::string skinName);
        // unload all enemy skins
        void unloadEnemySkins();

        // useful ? only used in Lobby -> should be a Lobby resources
        Texture2D* getLobbyBgTexture();

        Texture2D* setMapTexture(GameMaps= GameMaps::URBAN);
        Texture2D* getMapTexture();
        GameMaps getGameMap();

    private:
        const char *TEXTURES_FOLDER = "./textures/",
            *MAP_FOLDER = "./textures/maps/",
            *PLAYERSKIN_FOLDER = "./textures/skins/player/",
            *ENEMYSKIN_FOLDER = "./textures/skins/enemy/",
            *DONUT_SKIN_FOLDER = "./textures/skins/enemy/donut/",
            *KING_DONUT_SKIN_FOLDER = "./textures/skins/enemy/king_donut/",
            *CHAD_DONUT_SKIN_FOLDER = "./textures/skins/enemy/chad_donut/";

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
        std::array<std::unordered_map<std::string, EnemySkin>, enemyTypeStr.size()> enemySkins;
        Texture2D mapTexture, lobbyBgTexture;

        GameMaps loaded_map;

        // load all player skins info (once on init)
        bool loadPlayerSkinsInfo();
        // load all enemy skins info (once on init)
        bool loadEnemySkinsInfo();

        DrawManager();
};


#endif
