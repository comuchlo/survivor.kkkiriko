#include "draw_manager.hpp"

#include <array>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <raylib.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "../utils/utils.hpp"


DrawManager* DrawManager::instance = nullptr;

DrawManager::DrawManager() {
    const char *REGULAR_FONT_PATH = "./fonts/logofontik/logofontik.4f.ttf",
        *OUTLINE_FONT_PATH = "./fonts/logofontik/logofontik.extruded-4f.ttf";

    sys = System::getInstance();

    lobbyBgTexture.id = 0;
    mapTexture.id = 0;

    currRenderIndex = 0;
    // load render foreach
    for(auto i = renderSet.begin(); i != renderSet.cend(); i++) {
        *i = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);
    }

    // load fonts
    // check if the fonts are available
    if(fileExists(REGULAR_FONT_PATH)) {
        // note: NULL, 0 in code points and its count = default
        fontRegular = LoadFontEx(REGULAR_FONT_PATH, titleFontSize, NULL, 0);
        fontOutline = LoadFontEx(OUTLINE_FONT_PATH, titleFontSize, NULL, 0);
        fontAvailable = true;

    } else {
        Font
        fontRegular = GetFontDefault();
        fontOutline = fontRegular;
        fontAvailable = false;

    }

    if(fontAvailable) std::cout<<"INFO: Game font is available"<<std::endl;
    else std::cout<<"WARNING: Game font is not available"<<std::endl;

    // retrive (once and for all) every skins info
    if (!loadPlayerSkinsInfo())
        std::cout<< "ERROR: Error on retrieving player skins info"<<std::endl;

    update(); // to update actual screen
}

DrawManager::~DrawManager() {
    for(auto i = renderSet.begin(); i != renderSet.cend(); i++) {
        if(IsRenderTextureValid(*i)) // profilacto tactics
            UnloadRenderTexture(*i);
    }

    unloadPlayerSkins();
    setMapTexture(GameMaps::NONE);
    UnloadTexture(lobbyBgTexture);

    if(fontAvailable) {
        UnloadFont(fontRegular);
        UnloadFont(fontOutline);
    }
}

DrawManager* DrawManager::getInstance(){
    if (instance == nullptr){
            instance = new DrawManager();
    }
    return instance;
}

void DrawManager::drawRangeBar(int progress, int height) {
   	int progressLenght = (!progress) ? 0 : progress * 2.5;

   	DrawRectangle((RENDER_WIDTH / 2) - 127, height, 10, 19, GetColor(0x232323ff));//first end of bar
   	DrawRectangle((RENDER_WIDTH / 2) + 117, height + 5, 10, 19, GetColor(0x232323ff));//end of bar
   	DrawRectangle((RENDER_WIDTH / 2) - 127, height + 5, 254, 14, GetColor(0x232323ff));//outerBar
   	DrawRectangle((RENDER_WIDTH / 2) - 125, height + 7, 250, 10, WHITE);//innerBar
   	DrawRectangle((RENDER_WIDTH / 2) - 125, height + 7, progressLenght, 10, RED);//Master Volume Level

   	DrawText(TextFormat("%d", progress), (RENDER_WIDTH / 2) + 136, height + 2, 18, BLACK);//Master Volume Number
   	DrawText(TextFormat("%d", progress), (RENDER_WIDTH / 2) + 137, height + 3, 18, BLACK);//Master Volume Number
   	DrawText(TextFormat("%d", progress), (RENDER_WIDTH / 2) + 138, height + 4, 18, RED);//Master Volume Number

   	DrawRectangle((RENDER_WIDTH / 2) - 127 + progressLenght, height - 1, 10, 26, BLACK);//outerRangeCursor
   	DrawRectangle((RENDER_WIDTH / 2) - 125 + progressLenght, height + 1, 6, 22, RED);//innerRangeCursor
}

void DrawManager::drawText(const char *text, int x, int y, int fontSize, Color col) {
    if(fontAvailable) {
        DrawTextEx(fontRegular, text, {(float)x, (float)y}, fontSize, 0, col);
    } else {
        DrawText(text, x, y, fontSize, col);
    }
}

void DrawManager::drawTextSF(const char *text, int x, int y, int fontSize, Color col1, Color col2, Color col3) {
    if(fontAvailable) {
        DrawTextEx(fontRegular, text, {(float)x, (float)y}, fontSize, 0, col3);
        DrawTextEx(fontOutline, text, {(float)x, (float)y}, fontSize, 0, col1);
    } else {
        DrawText(text, x - 2, y - 2, fontSize, col1);
       	DrawText(text, x, y, fontSize, col2);
       	DrawText(text, x + 2, y + 2, fontSize, col3);
    }
}

void DrawManager::drawTextSFC(const char *text, int y, int fontSize, Color col1, Color col2, Color col3) {
    if(fontAvailable) {
        const float x = (float)RENDER_WIDTH/2 - MeasureTextEx(fontRegular, text, fontSize, 0).x/2;
        DrawTextEx(fontRegular, text, {x, (float)y}, fontSize, 0, col3);
        DrawTextEx(fontOutline, text, {x, (float)y}, fontSize, 0, col1);
    } else {
        const int x = (float)RENDER_WIDTH/2 - (float)MeasureText(text, fontSize)/2;
        DrawText(text, x - 2, y - 2, fontSize, col1);
       	DrawText(text, x, y, fontSize, col2);
       	DrawText(text, x + 2, y + 2, fontSize, col3);
    }
}

void DrawManager::drawArrowSF(float x, float y, float width, float height, float thick, bool verse, Color col1, Color col2, Color col3) {
   	if (!verse)  {
  		DrawLineEx((Vector2){x-2,y-2},(Vector2){x+width-2,y+(height/2)-2},thick,col1);
  		DrawLineEx((Vector2){x-2,y+height-2},(Vector2){x+width-2,y+(height/2)-2},thick,col1);

  		DrawLineEx((Vector2){x,y},(Vector2){x+width,y+(height/2)},thick,col2);
  		DrawLineEx((Vector2){x,y+height},(Vector2){x+width,y+(height/2)},thick,col2);

  		DrawLineEx((Vector2){x+2,y+2},(Vector2){x+width+2,y+(height/2)+2},thick,col3);
  		DrawLineEx((Vector2){x+2,y+height+2},(Vector2){x+width+2,y+(height/2)+2},thick,col3);
   	} else {
  		DrawLineEx((Vector2){x+width-2,y-2},(Vector2){x-2,y+(height/2)-2},thick,col1);
  		DrawLineEx((Vector2){x+width-2,y+height-2},(Vector2){x-2,y+(height/2)-2},thick,col1);

  		DrawLineEx((Vector2){x+width,y},(Vector2){x,y+(height/2)},thick,col2);
  		DrawLineEx((Vector2){x+width,y+height},(Vector2){x,y+(height/2)},thick,col2);

  		DrawLineEx((Vector2){x+width+2,y+2},(Vector2){x+2,y+(height/2)+2},thick,col3);
  		DrawLineEx((Vector2){x+width+2,y+height+2},(Vector2){x+2,y+(height/2)+2},thick,col3);
   	}
}

void DrawManager::drawTextSFCA(const char *text, int y, int fontSize, bool drawArrow, int arrowPadding, float arrowThickness, Color col1, Color col2, Color col3) {
    float halfTextLen, x;

    if(fontAvailable) {
        halfTextLen = MeasureTextEx(fontRegular, text, fontSize, 0).x/2;
        x = (float)RENDER_WIDTH/2 - halfTextLen;

        DrawTextEx(fontRegular, text, {x, (float)y}, fontSize, 0, col3);
        DrawTextEx(fontOutline, text, {x, (float)y}, fontSize, 0, col1);
    } else {
        halfTextLen = (float)MeasureText(text, fontSize)/2;
        x = (float)RENDER_WIDTH/2 - halfTextLen;

        DrawText(text, x - 2, y - 2, fontSize, col1);
       	DrawText(text, x, y, fontSize, col2);
       	DrawText(text, x + 2, y + 2, fontSize, col3);
    }

    if(drawArrow) {
        drawArrowSF(x - arrowPadding - fontSize, y, fontSize, fontSize, arrowThickness, true, col1, col2, col3);
        drawArrowSF(((float)RENDER_WIDTH / 2) + halfTextLen + arrowPadding, y, fontSize, fontSize, arrowThickness, false, col1, col2, col3);
    }
}


float DrawManager::measureText(const char *text, int fontSize) {
    return (fontAvailable) ?
        MeasureTextEx(fontRegular, text, fontSize, 0).x :
        (float)MeasureText(text, fontSize);
}

void DrawManager::drawRender() {
    DrawTexturePro(
        renderSet[currRenderIndex].texture,
        idealScreen, //source
        actualScreen, //dest
        {0.0f, 0.0f}, //origin
        0.0f, //rotation
        WHITE
    );
}

RenderTexture2D* DrawManager::currRender() {
    return &renderSet[currRenderIndex];
}

RenderTexture2D* DrawManager::prevRender() {
    int index = currRenderIndex-1;
    if(index < 0) index = renderSet.size()-1;

    return &renderSet[index];
}

void DrawManager::switchRender() {
    currRenderIndex++;
    if(currRenderIndex >= renderSet.size()) currRenderIndex = 0;
}

void DrawManager::update() { // to update actualScreen
    const auto [screenW, screenH] = sys->getScreenSizeWH();
    actualScreen = {0.0f, 0.0f, screenW, screenH };

    const double screenRatio = screenW / screenH, renderRatio = 16.0f/9.0f;

    // screenRatio != renderRatio ?
    if(std::abs(screenRatio - renderRatio) >  std::numeric_limits<double>::epsilon()) {
        if (screenRatio > renderRatio) { // add black bars lateraly
            actualScreen.width = (screenH*16.0f)/9.0f;
            actualScreen.x = screenW / 2 - actualScreen.width / 2;

        } else { // add bars vertically
            actualScreen.height = (screenW*9.0f)/16.0f;
            actualScreen.y = screenH / 2 - actualScreen.height / 2;
        }
    }
}

bool DrawManager::loadPlayerSkinsInfo() {
    int unvalidSkins = 0;

    std::cout<<"INFO: Loading player skins info"<<std::endl;

    // get all .png files in textures/playerskins
    FilePathList skinFiles = LoadDirectoryFilesEx(
        PLAYERSKIN_FOLDER,
        ".png",
        false
    );

    for(unsigned int i = 0; i < skinFiles.count; i++) {
        bool currValid = true;

        // get filename
        const std::string fileName = GetFileNameWithoutExt(skinFiles.paths[i]);

        //init skininfo
        PlayerSkinInfo skinInfo = {
            fileName.c_str(), // name
            0, // idleTotFrame
            0, // runTotFrame
            0, // attackTotFrame
            0, // kunaiTotFrame
            0, // topWidth
            0, // topHeight
            0, // bottomHeight
            0, // kunaiWidth
            0, // kunaiHeight
            0, // topIdleY
            0, // bottomIdleY
            0, // topRunY
            0, // bottomRunY
            0, // topAttackY
            0, // kunaiY
        };

        // check if .sfinfo correspective file exist
        std::ifstream fileInfo(PLAYERSKIN_FOLDER+fileName+".sfinfo");

        if(fileInfo) { // open succesfull
            std::string tmp;

            //first line:
            // <playerWidth> <playerTopHeight> <playerBottomHeight> <kunaiWidth> <kunaiHeight>
            if(std::getline(fileInfo, tmp)) {
                ////////// ATTANTION: uint8 IS char -> 6 = 48(='0')+6
                /// so when reading: uint8_t behave as char (:
                int width, topHeight, bottomHeight, kunaiWidth, kunaiHeight;
                if(!(std::istringstream (tmp) >> width >> topHeight >> bottomHeight >> kunaiWidth >> kunaiHeight)) {
                    currValid = false;
                }
                skinInfo.width = width;
                skinInfo.topHeight = topHeight;
                skinInfo.bottomHeight = bottomHeight;
                skinInfo.kunaiWidth = kunaiWidth;
                skinInfo.kunaiHeight = kunaiHeight;
            } else {
                currValid = false;
            }

            //second line:
            // <IdleTotFrame> <RunTotFrame> <AttackTotFrame> <kunaiTotFrame>
            if(std::getline(fileInfo, tmp)) {
                ////////// ATTANTION: uint8 IS char -> 6 = 48(='0')+6
                /// so when reading: uint8_t behave as char (:
                int idleTotFrame, runTotFrame, attackTotFrame, kunaiTotFrame;
                if(!(std::istringstream (tmp) >> idleTotFrame >> runTotFrame >> attackTotFrame >> kunaiTotFrame)) {
                    currValid = false;
                }
                skinInfo.idleTotFrame = idleTotFrame;
                skinInfo.runTotFrame = runTotFrame;
                skinInfo.attackTotFrame = attackTotFrame;
                skinInfo.kunaiTotFrame = kunaiTotFrame;
            } else {
                currValid = false;
            }

            //third line:
            // <IdleTopY> <IdleBottomY> <RunTopY> <RunBottomY> <AttackTopY> <kunaiY>
            if(std::getline(fileInfo, tmp)) {
                int topIdleY, bottomIdleY, topRunY, bottomRunY, topAttackY, kunaiY;
                if(!(std::istringstream (tmp) >> topIdleY >> bottomIdleY >> topRunY >> bottomRunY >> topAttackY >> kunaiY)) {
                    currValid = false;
                }
                skinInfo.topIdleY = topIdleY;
                skinInfo.bottomIdleY = bottomIdleY;
                skinInfo.topRunY = topRunY;
                skinInfo.bottomRunY = bottomRunY;
                skinInfo.topAttackY = topAttackY;
                skinInfo.kunaiY = kunaiY;


            } else {
                currValid = false;
            }
        } else {
            currValid = false;
        }

        if(currValid) {
            std::cout<<
                "INFO: Player skin info named '"<<
                fileName<<
                "' succesfully loaded"<<
                std::endl;

            // save result with zeroed-texture
            playerSkins.insert({fileName, {skinInfo, {0, 0, 0, 0, 0}}});
        } else {
            unvalidSkins++;

            std::cout<<
                "ERROR: Player skin info named '"<<
                fileName<<
                "' present errors"<<
                std::endl;
        }
    }

    if(unvalidSkins > 0) {
        std::cout<<
            "ERROR: "<<
            unvalidSkins<<
            " player skin(s) info contained errors"<<
            std::endl;
    } else {
        std::cout<<"INFO: All player skins info were succesfully loaded"<<std::endl;
    }

    return true;
}

std::vector<PlayerSkinInfo> DrawManager::getPlayerSkinsInfo() {
    std::vector<PlayerSkinInfo> skinsInfo;
    skinsInfo.reserve(playerSkins.size());

    for(auto& [key, value]: playerSkins) {
        skinsInfo.push_back(value.skinInfo);
    }

    return skinsInfo;
}

PlayerSkin* DrawManager::loadPlayerSkin(const char* skinName) {
    PlayerSkin* found;

    // load first if no name provided
    const char *name = (strcmp(skinName, "") == 0) ?
        skinName = playerSkins.begin()->first.c_str() :
        skinName;

    try {
        found = &playerSkins.at(name);

        if(!IsTextureValid(found->texture)) {
            char tempbuffer[100];
            sprintf(tempbuffer, "%s%s.png", PLAYERSKIN_FOLDER, name);
            found->texture = LoadTexture(tempbuffer);
        }
    } catch (const std::runtime_error e) {
        std::cout<<"ERROR: Error on loading player skin "<<name<<std::endl;
    }

    return found;
}

void DrawManager::unloadPlayerSkins() {
    for(auto& [key, value]: playerSkins) {
        if(IsTextureValid(value.texture)) {
            UnloadTexture(value.texture);
            value.texture.id = 0; // strong mark as unvalid
        }

    }
}

PlayerSkin* DrawManager::initSurvivorTextures(GameMaps map) {
    setMapTexture(map);
    PlayerSkin* playerSkin = loadPlayerSkin("");
    initializedMod = InitializedModality::TRAINING;
    return playerSkin;
}

void DrawManager::destroySurvivorTextures() {
    setMapTexture(GameMaps::NONE);
    unloadPlayerSkins();
    initializedMod = InitializedModality::NONE;
}

PlayerSkin* DrawManager::initTrainingTextures() {
    PlayerSkin* playerSkin = loadPlayerSkin("");
    initializedMod = InitializedModality::TRAINING;
    return playerSkin;
}

void DrawManager::destroyTrainingTextures() {
    unloadPlayerSkins();
    initializedMod = InitializedModality::NONE;
}

Texture2D* DrawManager::getLobbyBgTexture(){
    if(!IsTextureValid(this->lobbyBgTexture)){
        this->lobbyBgTexture= LoadTexture("./textures/kirikobg2.png");
    }
    return &(this->lobbyBgTexture);
}

Texture2D* DrawManager::setMapTexture(GameMaps map) {
    if(this->loaded_map != map) {
        UnloadTexture(this->mapTexture);
        this->mapTexture.id = 0; // strong mark as unvalid
        this->loaded_map = map;
        char tempbuffer[100];

        switch (map) {
            case GameMaps::NONE:
            case GameMaps::URBAN:
                sprintf(tempbuffer, "%smap_urban.png", TEXTURES_FOLDER);
                this->mapTexture= LoadTexture(tempbuffer);
                break;
            case GameMaps::GRASS:
                sprintf(tempbuffer, "%smap_grass.png", TEXTURES_FOLDER);
                this->mapTexture= LoadTexture(tempbuffer);
                break;
        }
    }

    return &(this->mapTexture);
}
Texture2D* DrawManager::getMapTexture() {
    if(this->loaded_map == GameMaps::NONE || !IsTextureValid(this->mapTexture)){
        this->setMapTexture();
    }
    return &(this->mapTexture);
}
