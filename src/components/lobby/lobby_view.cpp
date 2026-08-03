#include "lobby.hpp"


void Lobby::drawModality() { //: training , duel , survival , settings
    auto [renderWidth, renderHeight]= this->sys->getRenderSizeWH();
    RenderTexture render = sys->render;
    const int titleFont= this->sys->titlefontSize, buttonFont= this->sys->buttonFontSize, subTitleFont= this->sys->subTitleFontSize;

    BeginTextureMode(render);
    ClearBackground(BLACK);

    // background image
    DrawTexture(this->backgroundImage, 0, 0, WHITE); // render is same res as image

    // title
    this->drawer->drawTextSF("Kiriko", (renderWidth / 2) - ((float)MeasureText("Kiriko", titleFont) / 2), 50, titleFont, RED, BLACK, BLACK);
   	this->drawer->drawTextSF("and the donuts", (renderWidth / 2) - ((float)MeasureText("and the donuts", subTitleFont) / 2) + 2, 142, subTitleFont, RED, BLACK, BLACK);

   	//training
   	this->drawer->drawTextSF("Training", 12, 252, buttonFont, BLACK, BLACK, (this->choice == MenuSelection::TRAINING) ? RED : WHITE);

   	//duel
   	this->drawer->drawTextSF("Duel", 12, 302, buttonFont, BLACK, BLACK, (this->choice == MenuSelection::DUEL) ? RED : WHITE);

   	//survival
   	this->drawer->drawTextSF("Survival", 12, 352, buttonFont, BLACK, BLACK, (this->choice == MenuSelection::SURVIVAL) ? RED : WHITE);

   	//settings
   	this->drawer->drawTextSF("Settings", 12, 402, buttonFont, BLACK, BLACK, (this->choice == MenuSelection::SETTINGS) ? RED : WHITE);

   	//how to play
   	this->drawer->drawTextSF("How to play", 12, 452, buttonFont, BLACK, BLACK, (this->choice == MenuSelection::HOWTOPLAY) ? RED : WHITE);

   	//credits
   	this->drawer->drawTextSF("Credits", 12, 502, buttonFont, BLACK, BLACK, (this->choice == MenuSelection::CREDITS) ? RED : WHITE);

   	//exit game
   	this->drawer->drawTextSF("Exit game", 12, 552, buttonFont, BLACK, BLACK, (this->choice == MenuSelection::EXIT) ? RED : WHITE);

    EndTextureMode();

    //draw render (adapted to screen)
    DrawTexturePro(
        render.texture,
        (const Rectangle){0.0f, 0.0f, renderWidth, -renderHeight}, //source
        { 0.0f, 0.0f, sys->getScreenSizeWH().x, sys->getScreenSizeWH().y}, //dest
        {0.0f, 0.0f}, //origin
        0.0f, //rotation
        WHITE
    );
}
