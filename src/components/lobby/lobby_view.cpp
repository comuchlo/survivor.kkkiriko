#include <raylib.h>
#include "lobby.hpp"


void Lobby::drawLobby() { //: training , duel , survival , settings
    auto [screenWidth, screenHeight]= this->sys->getScreenSizeWH();
    int titleFont= this->sys->titlefontSize, buttonFont= this->sys->buttonFontSize, subTitleFont= this->sys->subTitleFontSize;

    ClearBackground(BLACK);

    // title
    this->drawer->drawTextSF("Kiriko", (screenWidth / 2) - (MeasureText("Kiriko", titleFont) / 2), 50, titleFont, RED, BLACK, BLACK);
   	this->drawer->drawTextSF("and the donuts", (screenWidth / 2) - (MeasureText("and the donuts", subTitleFont) / 2) + 2, 142, subTitleFont, RED, BLACK, BLACK);

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
}
