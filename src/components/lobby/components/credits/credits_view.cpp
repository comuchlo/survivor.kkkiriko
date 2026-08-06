#include "credits.hpp"
#include <raylib.h>

void Credits::drawModality() {
    const auto [renderWidth, renderHeight]= this->sys->getRenderSizeWH();
    RenderTexture render = sys->render;
    const int titleFont= this->sys->titlefontSize, buttonFont= this->sys->buttonFontSize,
        subTitleFont= this->sys->subTitleFontSize, textFont = this->sys->textFontSize;


	BeginTextureMode(render);
	ClearBackground(BLACK);

	DrawTexture(*this->backgroundImage, 0, 0, WHITE); // render is same res as image
	DrawRectangle(0, 0, renderWidth, renderHeight, GetColor(0xb0b0b05f));//darken bg

	BeginMode2D(this->game_manager->camera1);

		this->drawer->drawTextSF("Credits", (renderWidth * 0.5) - ((float)MeasureText("Credits", titleFont) / 2), 50, titleFont, RED, BLACK, BLACK);
		this->drawer->drawTextSF("Programmers", (renderWidth / 2) - ((float)MeasureText("Programmers", buttonFont) / 2), 200, buttonFont, RED, BLACK, BLACK);
		this->drawer->drawTextSF("Bardin Gabriele", (renderWidth / 2) - ((float)MeasureText("Bardin Gabriele", buttonFont) / 2), 260, buttonFont, BLACK, BLACK, RED);
		this->drawer->drawTextSF("Cassandra Maceira", (renderWidth / 2) - ((float)MeasureText("Cassandra Maceira", buttonFont) / 2), 310, buttonFont, BLACK, BLACK, RED);

		this->drawer->drawTextSF("Graphic Designer", (renderWidth / 2) - ((float)MeasureText("Graphic Designer", buttonFont) / 2), 410, buttonFont, RED, BLACK, BLACK);
		this->drawer->drawTextSF("Textures", (renderWidth / 2) - ((float)MeasureText("Textures", buttonFont) / 2), 460, buttonFont, RED, BLACK, BLACK);
		this->drawer->drawTextSF("Aron Capraro", (renderWidth / 2) - ((float)MeasureText("Aron Capraro", buttonFont) / 2), 510, buttonFont, BLACK, BLACK, RED);

		this->drawer->drawTextSF("Maps & Backgrounds", (renderWidth / 2) - ((float)MeasureText("Maps & Backgrounds", buttonFont) / 2), 610, buttonFont, RED, BLACK, BLACK);
		this->drawer->drawTextSF("Giacomo Pasqualini", (renderWidth / 2) - ((float)MeasureText("Giacomo Pasqualini", buttonFont) / 2), 660, buttonFont, BLACK, BLACK, RED);

		this->drawer->drawTextSF("Musics produced by", (renderWidth / 2) - ((float)MeasureText("Musics produced by", buttonFont) / 2), 760, buttonFont, RED, BLACK, BLACK);
		this->drawer->drawTextSF("Marllon Silva / xDeviruchi", (renderWidth / 2) - ((float)MeasureText("Marllon Silva / xDeviruchi", buttonFont) / 2), 820, buttonFont, BLACK, BLACK, RED);

		this->drawer->drawTextSF("Sounds", (renderWidth / 2) - ((float)MeasureText("Sounds", buttonFont) / 2), 920, buttonFont, RED, BLACK, BLACK);
		this->drawer->drawTextSF("Giacomo Pasqualini", (renderWidth / 2) - ((float)MeasureText("Giacomo Pasqualini", buttonFont) / 2), 970, buttonFont, BLACK, BLACK, RED);

		this->drawer->drawTextSF("Thanks for Playing!", (renderWidth / 2) - ((float)MeasureText("Thanks for Playing!", titleFont) / 2), this->CREDITS_HEIGHT_END+this->shiftDown, titleFont, RED, BLACK, BLACK);

		if(this->endedAutoScrool)
		    DrawText("(Press ESC to exit)", (renderWidth / 2) - ((float)MeasureText("(Press ESC to exit)", textFont) / 2), this->CREDITS_HEIGHT_END+this->shiftDown+95.0f, textFont, BLACK);

  EndMode2D();
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
