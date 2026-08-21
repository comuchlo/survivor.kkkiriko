#include "howtoplay.hpp"
#include "../../../../core/draw_manager.hpp"

void HowToPlay::drawModality() {
    const float renderWidth = drawer->RENDER_WIDTH, renderHeight = drawer->RENDER_HEIGHT;
    const int titleFont= drawer->titleFontSize, buttonFont= drawer->buttonFontSize,
        subTitleFont= drawer->subTitleFontSize, textFont = drawer->textFontSize;


	DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image
	DrawRectangle(0, 0, renderWidth, renderHeight, GetColor(0xb0b0b05f));//darken bg

	BeginMode2D(game_manager->camera1);
        drawer->drawTextSFC("How to Play", 50, titleFont, RED, BLACK, BLACK);
    	drawer->drawTextSFC("Hi and welcome to 'Kiriko and the donuts!'", 250, subTitleFont, BLACK, BLACK, RED);


		drawer->drawTextSF("Basic Commands:", 12, 350, subTitleFont, BLACK, BLACK, RED);
		drawer->drawText("Use arrows or WASD to move in the menus and ENTER to confirm.", 15, 420, textFont, BLACK);
		drawer->drawText("In order to exit the game whenever you want, you can always use alt+k ", 15, 450, textFont, BLACK);

		drawer->drawTextSF("In-game Commands:", 12, 530, subTitleFont, BLACK, BLACK, RED);
		drawer->drawTextSF("Pause:", 15, 600, textFont, BLACK, BLACK, RED);
		drawer->drawText(" whenever you are in Training or Survival or Duel, you can always pause", 15 + drawer->measureText("Pause:", textFont), 600, textFont, BLACK);
		drawer->drawText("the game using ESCAPE, you will then use the mouse to move around the menu,", 35, 630, textFont, BLACK);
		drawer->drawText("enter again ESCAPE to quick resume.", 35, 660, textFont, BLACK);

		drawer->drawTextSF("Training:", 15, 690, textFont, BLACK, BLACK, RED);
		drawer->drawText(" here you can practice your aim with your mouse against", 15 + drawer->measureText("Training:", textFont), 690, textFont, BLACK);
		drawer->drawText("the enemies (CLICK button enabled)", 35, 720, textFont, BLACK);

		drawer->drawTextSF("Survival and Duel:", 15, 750, textFont, BLACK, BLACK, RED);
		drawer->drawText(" these two games are endless PvE (Player vs Enemies),", 15 + drawer->measureText("Survival and Duel:", textFont), 750, textFont, BLACK);
		drawer->drawText("hold on as long as you can for greater records!", 35, 780, textFont, BLACK);
		drawer->drawText("As the endless says, there is no ending in it except in duel", 35, 810, textFont, BLACK);
		drawer->drawText("when a player dies, the other wins.", 35, 840, textFont, BLACK);

		drawer->drawTextSFC("Have a great experience playing all of them!", 910, buttonFont, BLACK, BLACK, RED);

		// drawer->drawTextSF("How to Play", (renderWidth / 2) - ((float)MeasureText("How to Play", titleFont) / 2), 50, titleFont, RED, BLACK, BLACK);
		// drawer->drawTextSF("Hi and welcome to 'Kiriko and the donuts!'", (renderWidth / 2) - ((float)MeasureText("Hi and welcome to 'Kiriko and the donuts!'", subTitleFont) / 2), 250, subTitleFont, BLACK, BLACK, RED);

		// drawer->drawTextSF("Basic Commands:", 12, 350, subTitleFont, BLACK, BLACK, RED);
		// DrawText("Use arrows or WASD to move in the menus and ENTER to confirm.", 15, 420, textFont, BLACK);
		// DrawText("In order to exit the game whenever you want, you can always use alt+k ", 15, 450, textFont, BLACK);

		// drawer->drawTextSF("In-game Commands:", 12, 530, subTitleFont, BLACK, BLACK, RED);
		// drawer->drawTextSF("Pause:", 15, 600, textFont, BLACK, BLACK, RED);
		// DrawText(" whenever you are in Training or Survival or Duel, you can always pause", 15 + MeasureText("Pause:", textFont), 600, textFont, BLACK);
		// DrawText("the game using ESCAPE, you will then use the mouse to move around the menu,", 35, 630, textFont, BLACK);
		// DrawText("enter again ESCAPE to quick resume.", 35, 660, textFont, BLACK);

		// drawer->drawTextSF("Training:", 15, 690, textFont, BLACK, BLACK, RED);
		// DrawText(" here you can practice your aim with your mouse against", 15 + MeasureText("Training:", textFont), 690, textFont, BLACK);
		// DrawText("the enemies (CLICK button enabled)", 35, 720, textFont, BLACK);

		// drawer->drawTextSF("Survival and Duel:", 15, 750, textFont, BLACK, BLACK, RED);
		// DrawText(" these two games are endless PvE (Player vs Enemies),", 15 + MeasureText("Survival and Duel:", textFont), 750, textFont, BLACK);
		// DrawText("hold on as long as you can for greater records!", 35, 780, textFont, BLACK);
		// DrawText("As the endless says, there is no ending in it except in duel", 35, 810, textFont, BLACK);
		// DrawText("when a player dies, the other wins.", 35, 840, textFont, BLACK);

		// drawer->drawTextSF("Have a great experience playing all of them!", (renderWidth / 2) - ((float)MeasureText("Have a great experience playing all of them!", buttonFont) / 2), 910, buttonFont, BLACK, BLACK, RED);

     EndMode2D();
}
