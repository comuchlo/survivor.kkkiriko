#include "lobbymenu.hpp"


void LobbyMenu::drawModality() { //: training , duel , survival , settings
    // const float renderWidth = drawer->RENDER_WIDTH, renderHeight = drawer->RENDER_HEIGHT;
    const int titleFont= drawer->titleFontSize, buttonFont= drawer->buttonFontSize,
        subTitleFont= drawer->subTitleFontSize;

    const int xOffset = 12; // const x offset
    int currH = 50; // for draw calls height

    // background image
    DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image

    // title
    drawer->drawTextSFC("Kiriko", currH, titleFont, RED, BLACK, BLACK);
    currH+= 92;
   	drawer->drawTextSFC("and the donuts", currH, subTitleFont, RED, BLACK, BLACK);

   	//training
    currH+= 110;
   	drawer->drawTextSF("Training", xOffset, currH, buttonFont, BLACK, BLACK, (choice == MenuSelection::TRAINING) ? RED : WHITE);

   	//duel
    currH+= 50;
   	drawer->drawTextSF("Duel", xOffset, currH, buttonFont, BLACK, BLACK, (choice == MenuSelection::DUEL) ? RED : WHITE);

   	//survival
    currH+= 50;
   	drawer->drawTextSF("Survival", xOffset, currH, buttonFont, BLACK, BLACK, (choice == MenuSelection::SURVIVAL) ? RED : WHITE);

   	//settings
    currH+= 50;
   	drawer->drawTextSF("Settings", xOffset, currH, buttonFont, BLACK, BLACK, (choice == MenuSelection::SETTINGS) ? RED : WHITE);

   	//how to play
    currH+= 50;
   	drawer->drawTextSF("How to play", xOffset, currH, buttonFont, BLACK, BLACK, (choice == MenuSelection::HOWTOPLAY) ? RED : WHITE);

   	//credits
    currH+= 50;
   	drawer->drawTextSF("Credits", xOffset, currH, buttonFont, BLACK, BLACK, (choice == MenuSelection::CREDITS) ? RED : WHITE);

   	//exit game
    currH+= 50;
   	drawer->drawTextSF("Exit game", xOffset, currH, buttonFont, BLACK, BLACK, (choice == MenuSelection::EXIT) ? RED : WHITE);
}
