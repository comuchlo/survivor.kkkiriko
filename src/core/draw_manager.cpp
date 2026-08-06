#include "draw_manager.hpp"


    DrawManager* DrawManager::instance = nullptr;

    DrawManager::DrawManager() {
        this->sys = System::getInstance();
    }

    DrawManager::~DrawManager() {

    }

	DrawManager* DrawManager::getInstance(){
        if (instance == nullptr){
                instance = new DrawManager();
        }
        return instance;
    }

    void DrawManager::drawTextSF(const char *text, int x, int y, int font, Color col1, Color col2, Color col3) {
       	DrawText(text, x - 2, y - 2, font, col1);
       	DrawText(text, x, y, font, col2);
       	DrawText(text, x + 2, y + 2, font, col3);
    }

    void DrawManager::drawRangeBar(int progress, int height) {
        auto [renderWidth, renderHeight]= this->sys->getRenderSizeWH();
       	int progressLenght = (!progress) ? 0 : progress * 2.5;

       	DrawRectangle((renderWidth / 2) - 127, height, 10, 19, GetColor(0x232323ff));//first end of bar
       	DrawRectangle((renderWidth / 2) + 117, height + 5, 10, 19, GetColor(0x232323ff));//end of bar
       	DrawRectangle((renderWidth / 2) - 127, height + 5, 254, 14, GetColor(0x232323ff));//outerBar
       	DrawRectangle((renderWidth / 2) - 125, height + 7, 250, 10, WHITE);//innerBar
       	DrawRectangle((renderWidth / 2) - 125, height + 7, progressLenght, 10, RED);//Master Volume Level

       	DrawText(TextFormat("%d", progress), (renderWidth / 2) + 136, height + 2, 18, BLACK);//Master Volume Number
       	DrawText(TextFormat("%d", progress), (renderWidth / 2) + 137, height + 3, 18, BLACK);//Master Volume Number
       	DrawText(TextFormat("%d", progress), (renderWidth / 2) + 138, height + 4, 18, RED);//Master Volume Number

       	DrawRectangle((renderWidth / 2) - 127 + progressLenght, height - 1, 10, 26, BLACK);//outerRangeCursor
       	DrawRectangle((renderWidth / 2) - 125 + progressLenght, height + 1, 6, 22, RED);//innerRangeCursor
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
