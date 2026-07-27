#include <raylib.h>
#include "system.hpp"
#include "draw_manager.hpp"


    void DrawManager::drawTextSF(const char *text, int x, int y, int font, Color col1, Color col2, Color col3) {
        auto [screenHeight,screenWidth]= this->sys->getScreenSize();

       	DrawText(text, x - 2, y - 2, font, col1);
       	DrawText(text, x, y, font, col2);
       	DrawText(text, x + 2, y + 2, font, col3);
    }

    void DrawManager::drawRangeBar(int progress, int height) {
        auto [screenHeight,screenWidth]= this->sys->getScreenSize();
       	int progressLenght = (!progress) ? 0 : progress * 2.5;

       	DrawRectangle((screenWidth / 2) - 127, height, 10, 19, GetColor(0x232323ff));//first end of bar
       	DrawRectangle((screenWidth / 2) + 117, height + 5, 10, 19, GetColor(0x232323ff));//end of bar
       	DrawRectangle((screenWidth / 2) - 127, height + 5, 254, 14, GetColor(0x232323ff));//outerBar
       	DrawRectangle((screenWidth / 2) - 125, height + 7, 250, 10, WHITE);//innerBar
       	DrawRectangle((screenWidth / 2) - 125, height + 7, progressLenght, 10, RED);//Master Volume Level

       	DrawText(TextFormat("%d", progress), (screenWidth / 2) + 136, height + 2, 18, BLACK);//Master Volume Number
       	DrawText(TextFormat("%d", progress), (screenWidth / 2) + 137, height + 3, 18, BLACK);//Master Volume Number
       	DrawText(TextFormat("%d", progress), (screenWidth / 2) + 138, height + 4, 18, RED);//Master Volume Number

       	DrawRectangle((screenWidth / 2) - 127 + progressLenght, height - 1, 10, 26, BLACK);//outerRangeCursor
       	DrawRectangle((screenWidth / 2) - 125 + progressLenght, height + 1, 6, 22, RED);//innerRangeCursor
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

    void DrawManager::drawLobby() { //: training , duel , survival , settings
        int choice= this->sys->choice;
        auto [screenHeight,screenWidth]= this->sys->getScreenSize();
        int titleFont= this->sys->titlefontSize, buttonFont= this->sys->buttonFontSize, subTitleFont= this->sys->subTitleFontSize;

        ClearBackground(BLACK);

        // title
        drawTextSF("Kiriko", (screenWidth / 2) - (MeasureText("Kiriko", titleFont) / 2), 50, titleFont, RED, BLACK, BLACK);
       	drawTextSF("and the donuts", (screenWidth / 2) - (MeasureText("and the donuts", subTitleFont) / 2) + 2, 142, subTitleFont, RED, BLACK, BLACK);

       	//training
       	drawTextSF("Training", 12, 252, buttonFont, BLACK, BLACK, (choice == 1) ? RED : WHITE);

       	//duel
       	drawTextSF("Duel", 12, 302, buttonFont, BLACK, BLACK, (choice == 2) ? RED : WHITE);

       	//survival
       	drawTextSF("Survival", 12, 352, buttonFont, BLACK, BLACK, (choice == 3) ? RED : WHITE);

       	//settings
       	drawTextSF("Settings", 12, 402, buttonFont, BLACK, BLACK, (choice == 4) ? RED : WHITE);

       	//how to play
       	drawTextSF("How to play", 12, 452, buttonFont, BLACK, BLACK, (choice == 5) ? RED : WHITE);

       	//credits
       	drawTextSF("Credits", 12, 502, buttonFont, BLACK, BLACK, (choice == 6) ? RED : WHITE);

       	//exit game
       	drawTextSF("Exit game", 12, 552, buttonFont, BLACK, BLACK, (choice == 7) ? RED : WHITE);
    }
