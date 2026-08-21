#include "credits.hpp"
#include <raylib.h>

void Credits::drawModality() {
    const float renderW = drawer->RENDER_WIDTH, renderH = drawer->RENDER_HEIGHT;
    const int titleFont= drawer->titleFontSize, buttonFont= drawer->buttonFontSize,
        subTitleFont= drawer->subTitleFontSize, textFont = drawer->textFontSize;


	DrawTexture(*backgroundImage, 0, 0, WHITE); // render is same res as image
	DrawRectangle(0, 0, renderW, renderH, GetColor(0xb0b0b05f));//darken bg

	BeginMode2D(game_manager->camera1);
		drawer->drawTextSFC("Credits", 50, titleFont, RED, BLACK, BLACK);
		drawer->drawTextSFC("Programmers", 200, buttonFont, RED, BLACK, BLACK);
		drawer->drawTextSFC("Bardin Gabriele", 260, buttonFont, BLACK, BLACK, RED);
		drawer->drawTextSFC("Cassandra Maceira", 310, buttonFont, BLACK, BLACK, RED);

		drawer->drawTextSFC("Graphic Designer", 410, buttonFont, RED, BLACK, BLACK);
		drawer->drawTextSFC("Textures", 460, buttonFont, RED, BLACK, BLACK);
		drawer->drawTextSFC("Aron Capraro", 510, buttonFont, BLACK, BLACK, RED);

		drawer->drawTextSFC("Maps & Backgrounds", 610, buttonFont, RED, BLACK, BLACK);
		drawer->drawTextSFC("Giacomo Pasqualini", 660, buttonFont, BLACK, BLACK, RED);

		drawer->drawTextSFC("Musics produced by", 760, buttonFont, RED, BLACK, BLACK);
		drawer->drawTextSFC("Marllon Silva / xDeviruchi", 820, buttonFont, BLACK, BLACK, RED);

		drawer->drawTextSFC("Sounds", 920, buttonFont, RED, BLACK, BLACK);
		drawer->drawTextSFC("Giacomo Pasqualini", 970, buttonFont, BLACK, BLACK, RED);

		if(!stoppedLastText)
		    drawer->drawTextSFC("Thanks for Playing!", CREDITS_HEIGHT_END, titleFont, RED, BLACK, BLACK);

		// drawer->drawTextSF("Programmers", (renderW / 2) - ((float)MeasureText("Programmers", buttonFont) / 2), 200, buttonFont, RED, BLACK, BLACK);
		// drawer->drawTextSF("Bardin Gabriele", (renderW / 2) - ((float)MeasureText("Bardin Gabriele", buttonFont) / 2), 260, buttonFont, BLACK, BLACK, RED);
		// drawer->drawTextSF("Cassandra Maceira", (renderW / 2) - ((float)MeasureText("Cassandra Maceira", buttonFont) / 2), 310, buttonFont, BLACK, BLACK, RED);

		// drawer->drawTextSF("Graphic Designer", (renderW / 2) - ((float)MeasureText("Graphic Designer", buttonFont) / 2), 410, buttonFont, RED, BLACK, BLACK);
		// drawer->drawTextSF("Textures", (renderW / 2) - ((float)MeasureText("Textures", buttonFont) / 2), 460, buttonFont, RED, BLACK, BLACK);
		// drawer->drawTextSF("Aron Capraro", (renderW / 2) - ((float)MeasureText("Aron Capraro", buttonFont) / 2), 510, buttonFont, BLACK, BLACK, RED);

		// drawer->drawTextSF("Maps & Backgrounds", (renderW / 2) - ((float)MeasureText("Maps & Backgrounds", buttonFont) / 2), 610, buttonFont, RED, BLACK, BLACK);
		// drawer->drawTextSF("Giacomo Pasqualini", (renderW / 2) - ((float)MeasureText("Giacomo Pasqualini", buttonFont) / 2), 660, buttonFont, BLACK, BLACK, RED);

		// drawer->drawTextSF("Musics produced by", (renderW / 2) - ((float)MeasureText("Musics produced by", buttonFont) / 2), 760, buttonFont, RED, BLACK, BLACK);
		// drawer->drawTextSF("Marllon Silva / xDeviruchi", (renderW / 2) - ((float)MeasureText("Marllon Silva / xDeviruchi", buttonFont) / 2), 820, buttonFont, BLACK, BLACK, RED);

		// drawer->drawTextSF("Sounds", (renderW / 2) - ((float)MeasureText("Sounds", buttonFont) / 2), 920, buttonFont, RED, BLACK, BLACK);
		// drawer->drawTextSF("Giacomo Pasqualini", (renderW / 2) - ((float)MeasureText("Giacomo Pasqualini", buttonFont) / 2), 970, buttonFont, BLACK, BLACK, RED);

		// if(!stoppedLastText)
		//     drawer->drawTextSF("Thanks for Playing!", (renderW / 2) - ((float)MeasureText("Thanks for Playing!", titleFont) / 2), CREDITS_HEIGHT_END, titleFont, RED, BLACK, BLACK);
  EndMode2D();

  if(stoppedLastText)
      drawer->drawTextSFC("Thanks for Playing!", (float)drawer->RENDER_HEIGHT/2 - (float)titleFont/2, titleFont, RED, BLACK, BLACK);
  if(endedAutoScrool)
      drawer->drawText("(Press ESC to exit)", (renderW / 2) - (drawer->measureText("(Press ESC to exit)", textFont) / 2), (float)drawer->RENDER_HEIGHT/2 + (float)titleFont/2 +5.0f, textFont, BLACK);

  // if(stoppedLastText)
  //     drawer->drawTextSF("Thanks for Playing!", (renderW / 2) - ((float)MeasureText("Thanks for Playing!", titleFont) / 2), (float)drawer->RENDER_HEIGHT/2 - (float)titleFont/2, titleFont, RED, BLACK, BLACK);
  // if(endedAutoScrool)
  //     DrawText("(Press ESC to exit)", (renderW / 2) - ((float)MeasureText("(Press ESC to exit)", textFont) / 2), (float)drawer->RENDER_HEIGHT/2 + (float)titleFont/2 +5.0f, textFont, BLACK);
}
