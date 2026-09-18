#include "howtoplay.hpp"
#include "../../../../core/draw_manager.hpp"

void HowToPlay::drawModality() {
    const float renderWidth = drawer->RENDER_WIDTH, renderHeight = drawer->RENDER_HEIGHT;
    const int titleFont= drawer->titleFontSize, buttonFont= drawer->buttonFontSize,
        subTitleFont= drawer->subTitleFontSize, textFont = drawer->textFontSize;

    int currH = 50; // for draw calls height

	DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image
	DrawRectangle(0, 0, renderWidth, renderHeight, GetColor(0xb0b0b05f));//darken bg

	BeginMode2D(game_manager->cameras[0]);
        drawer->drawTextSFC("How to Play", currH, titleFont, RED, BLACK, BLACK);
        currH+= 200;
    	drawer->drawTextSFC("Hi and welcome to 'Kiriko and the donuts!'", currH, subTitleFont, BLACK, BLACK, RED);


        currH+= 100;
		drawer->drawTextSF("Basic Commands:", 12, currH, subTitleFont, BLACK, BLACK, RED);
		currH+= 70;
		drawer->drawText("Use arrows or WASD to move in the menus and ENTER to confirm.", 15, currH, textFont, BLACK);
		currH+= 30;
		drawer->drawText("In order to exit the game whenever you want, you can always use alt+k ", 15, currH, textFont, BLACK);

		currH+= 80;
		drawer->drawTextSF("In-game Commands:", 12, currH, subTitleFont, BLACK, BLACK, RED);
		currH+= 70;
		drawer->drawTextSF("Pause:", 15, currH, textFont, BLACK, BLACK, RED);
		drawer->drawText(" whenever you are in Training or Survival or Duel, you can always pause", 15 + drawer->measureText("Pause:", textFont), currH, textFont, BLACK);
		currH+= 30;
		drawer->drawText("the game using ESCAPE, you will then use the mouse to move around the menu,", 35, currH, textFont, BLACK);
		currH+= 30;
		drawer->drawText("enter again ESCAPE to quick resume.", 35, currH, textFont, BLACK);

		currH+= 30;
		drawer->drawTextSF("Training:", 15, currH, textFont, BLACK, BLACK, RED);
		drawer->drawText(" here you can practice your aim with your mouse against", 15 + drawer->measureText("Training:", textFont), currH, textFont, BLACK);
		currH+= 30;
		drawer->drawText("the enemies (CLICK button enabled)", 35, currH, textFont, BLACK);

		currH+= 30;
		drawer->drawTextSF("Survival and Duel:", 15, currH, textFont, BLACK, BLACK, RED);
		drawer->drawText(" these two games are endless PvE (Player vs Enemies),", 15 + drawer->measureText("Survival and Duel:", textFont), currH, textFont, BLACK);
		currH+= 30;
		drawer->drawText("hold on as long as you can for greater records!", 35, currH, textFont, BLACK);
		currH+= 30;
		drawer->drawText("As the endless says, there is no ending in it except in duel", 35, currH, textFont, BLACK);
		currH+= 30;
		drawer->drawText("when a player dies, the other wins.", 35, currH, textFont, BLACK);

		currH+= 70;
		drawer->drawTextSFC("Have a great experience playing all of them!", currH, buttonFont, BLACK, BLACK, RED);
     EndMode2D();
}
