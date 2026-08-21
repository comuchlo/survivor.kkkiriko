#include "draw_manager.hpp"

#include <array>
#include <cstdio>
#include <iostream>
#include <limits>
#include <raylib.h>
#include "../utils/utils.hpp"


DrawManager* DrawManager::instance = nullptr;

DrawManager::DrawManager() {
    const char *REGULAR_FONT_PATH = "./fonts/logofontik/logofontik.4f.ttf",
        *OUTLINE_FONT_PATH = "./fonts/logofontik/logofontik.extruded-4f.ttf";

    sys = System::getInstance();

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
        fontRegular = {0};
        fontOutline = {0};
        fontAvailable = false;

    }

    std::cout<<"FONT IS AVAILABLE ? " << ((fontAvailable) ? "YES" : "NO")<<std::endl;

    update(); // to update actual screen
}

DrawManager::~DrawManager() {
    for(auto i = renderSet.begin(); i != renderSet.cend(); i++) {
        UnloadRenderTexture(*i);
    }

    UnloadTexture(kunaiTexture);
    UnloadTexture(playerTexture);
    UnloadTexture(mapTexture);
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

// drawTextSF but x-axis-centered based on RENDER_WIDTH
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

void DrawManager::initSurvivorTextures(GAME_MAPS map){
    this->playerTexture= LoadTexture("./textures/kiriko.png");
    this->kunaiTexture= LoadTexture("./textures/kunai.png");
    this->setMapTexture(map);
}

void DrawManager::destroySurvivorTextures(){
    UnloadTexture(this->playerTexture);
    UnloadTexture(this->kunaiTexture);
    UnloadTexture(this->mapTexture);
}

Texture2D* DrawManager::getPlayerTexture(){
    if(!IsTextureValid(this->playerTexture)){
        this->playerTexture= LoadTexture("./textures/kiriko.png");
    }
    return &(this->playerTexture);
}
Texture2D* DrawManager::getKunaiTexture(){
    if(!IsTextureValid(this->kunaiTexture)){ //considering to skip this check
        this->kunaiTexture= LoadTexture("./textures/kunai.png");
    }
    return &(this->kunaiTexture);
}
Texture2D* DrawManager::getLobbyBgTexture(){
    if(!IsTextureValid(this->lobbyBgTexture)){
        this->lobbyBgTexture= LoadTexture("./textures/kirikobg2.png");
    }
    return &(this->lobbyBgTexture);
}

Texture2D* DrawManager::setMapTexture(GAME_MAPS map){
    switch (map) {
        case GAME_MAPS::NONE:
        case GAME_MAPS::URBAN:
            this->mapTexture= LoadTexture("./textures/map_urban.png");
            this->loaded_map= GAME_MAPS::URBAN;
            break;
        case GAME_MAPS::GRASS:
            this->mapTexture= LoadTexture("./textures/map_grass.png");
            this->loaded_map= GAME_MAPS::GRASS;
            break;
    }
    return &(this->mapTexture);
}
Texture2D* DrawManager::getMapTexture(){
    if(this->loaded_map == GAME_MAPS::NONE || !IsTextureValid(this->mapTexture)){
        this->setMapTexture();
    }
    return &(this->mapTexture);
}
