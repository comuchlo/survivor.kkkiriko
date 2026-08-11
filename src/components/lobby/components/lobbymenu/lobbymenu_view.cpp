#include "lobbymenu.hpp"


void LobbyMenu::drawModality() { //: training , duel , survival , settings
    const float renderWidth = drawer->RENDER_WIDTH, renderHeight = drawer->RENDER_HEIGHT;
    const int titleFont= sys->titlefontSize, buttonFont= sys->buttonFontSize,
        subTitleFont= sys->subTitleFontSize;

    // background image
    DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image

    // title
    drawer->drawTextSF("Kiriko", (renderWidth / 2) - ((float)MeasureText("Kiriko", titleFont) / 2), 50, titleFont, RED, BLACK, BLACK);
   	drawer->drawTextSF("and the donuts", (renderWidth / 2) - ((float)MeasureText("and the donuts", subTitleFont) / 2) + 2, 142, subTitleFont, RED, BLACK, BLACK);

   	//training
   	drawer->drawTextSF("Training", 12, 252, buttonFont, BLACK, BLACK, (choice == MenuSelection::TRAINING) ? RED : WHITE);

   	//duel
   	drawer->drawTextSF("Duel", 12, 302, buttonFont, BLACK, BLACK, (choice == MenuSelection::DUEL) ? RED : WHITE);

   	//survival
   	drawer->drawTextSF("Survival", 12, 352, buttonFont, BLACK, BLACK, (choice == MenuSelection::SURVIVAL) ? RED : WHITE);

   	//settings
   	drawer->drawTextSF("Settings", 12, 402, buttonFont, BLACK, BLACK, (choice == MenuSelection::SETTINGS) ? RED : WHITE);

   	//how to play
   	drawer->drawTextSF("How to play", 12, 452, buttonFont, BLACK, BLACK, (choice == MenuSelection::HOWTOPLAY) ? RED : WHITE);

   	//credits
   	drawer->drawTextSF("Credits", 12, 502, buttonFont, BLACK, BLACK, (choice == MenuSelection::CREDITS) ? RED : WHITE);

   	//exit game
   	drawer->drawTextSF("Exit game", 12, 552, buttonFont, BLACK, BLACK, (choice == MenuSelection::EXIT) ? RED : WHITE);

}
