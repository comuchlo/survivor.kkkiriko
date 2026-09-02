#include "credits.hpp"
#include <raylib.h>

void Credits::drawModality() {
    const float renderW = drawer->RENDER_WIDTH, renderH = drawer->RENDER_HEIGHT;
    const int titleFont= drawer->titleFontSize, buttonFont= drawer->buttonFontSize,
        subTitleFont= drawer->subTitleFontSize, textFont = drawer->textFontSize;

    int currH = 50; // for draw calls height

	DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image
	DrawRectangle(0, 0, renderW, renderH, GetColor(0xb0b0b05f));//darken bg

	BeginMode2D(game_manager->camera1);
		drawer->drawTextSFC("Credits", currH, titleFont, RED, BLACK, BLACK);
		currH+= 150;
		drawer->drawTextSFC("Programmers", currH, buttonFont, RED, BLACK, BLACK);
		currH+= 60;
		drawer->drawTextSFC("Bardin Gabriele", currH, buttonFont, BLACK, BLACK, RED);
		currH+= 50;
		drawer->drawTextSFC("Cassandra Maceira", currH, buttonFont, BLACK, BLACK, RED);

		currH+= 100;
		drawer->drawTextSFC("Graphic Designer", currH, buttonFont, RED, BLACK, BLACK);
		currH+= 50;
		drawer->drawTextSFC("Textures", currH, buttonFont, RED, BLACK, BLACK);
		currH+= 60;
		drawer->drawTextSFC("Aron Capraro", currH, buttonFont, BLACK, BLACK, RED);

		currH+= 100;
		drawer->drawTextSFC("Maps & Backgrounds", currH, buttonFont, RED, BLACK, BLACK);
		currH+= 60;
		drawer->drawTextSFC("Giacomo Pasqualini", currH, buttonFont, BLACK, BLACK, RED);

		currH+= 100;
		drawer->drawTextSFC("Musics produced by", currH, buttonFont, RED, BLACK, BLACK);
		currH+= 60;
		drawer->drawTextSFC("Marllon Silva / xDeviruchi", currH, buttonFont, BLACK, BLACK, RED);

		currH+= 100;
		drawer->drawTextSFC("Sounds", currH, buttonFont, RED, BLACK, BLACK);
		currH+= 60;
		drawer->drawTextSFC("Giacomo Pasqualini", currH, buttonFont, BLACK, BLACK, RED);

		if(!stoppedLastText) {
		    currH = CREDITS_HEIGHT_END;
		    drawer->drawTextSFC("Thanks for Playing!", CREDITS_HEIGHT_END, titleFont, RED, BLACK, BLACK);
		}
  EndMode2D();

  if(stoppedLastText) {
      currH = (float)drawer->RENDER_HEIGHT/2 - (float)titleFont/2;
      drawer->drawTextSFC("Thanks for Playing!", currH, titleFont, RED, BLACK, BLACK);

      if(endedAutoScrool) {
          currH+= (float)titleFont/2 +25.0f;
          drawer->drawText("(Press ESC to exit)", (renderW / 2) - (drawer->measureText("(Press ESC to exit)", textFont) / 2), currH, textFont, BLACK);
      }
  }
}
