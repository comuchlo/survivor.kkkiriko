#include "draw_manager.hpp"

#include <limits>
#include <raylib.h>


DrawManager* DrawManager::instance = nullptr;

DrawManager::DrawManager() {
    sys = System::getInstance();
    render = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);

    update(); // to update actual screen
}

DrawManager::~DrawManager() {
    UnloadRenderTexture(render);
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
   	int progressLenght = (!progress) ? 0 : progress * 2.5;

   	DrawRectangle((RENDER_WIDTH / 2) - 127, height, 10, 19, GetColor(0x232323ff));//first end of bar
   	DrawRectangle((RENDER_WIDTH / 2) + 117, height + 5, 10, 19, GetColor(0x232323ff));//end of bar
   	DrawRectangle((RENDER_WIDTH / 2) - 127, height + 5, 254, 14, GetColor(0x232323ff));//outerBar
   	DrawRectangle((RENDER_WIDTH / 2) - 125, height + 7, 250, 10, WHITE);//innerBar
   	DrawRectangle((RENDER_WIDTH / 2) - 125, height + 7, progressLenght, 10, RED);//Master Volume Level

   	DrawText(TextFormat("%d", progress), (RENDER_WIDTH / 2) + 136, height + 2, 18, BLACK);//Master Volume Number
   	DrawText(TextFormat("%d", progress), (RENDER_WIDTH / 2) + 137, height + 3, 18, BLACK);//Master Volume Number
   	DrawText(TextFormat("%d", progress), (RENDER_WIDTH / 2) + 138, height + 4, 18, RED);//Master Volume Number

   	DrawRectangle((RENDER_WIDTH / 2) - 127 + progressLenght, height - 1, 10, 26, BLACK);//outerRangeCursor
   	DrawRectangle((RENDER_WIDTH / 2) - 125 + progressLenght, height + 1, 6, 22, RED);//innerRangeCursor
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

void DrawManager::drawRender() {
    DrawTexturePro(
        render.texture,
        idealScreen, //source
        actualScreen, //dest
        {0.0f, 0.0f}, //origin
        0.0f, //rotation
        WHITE
    );
}

void DrawManager::update() { // to update actualScreen
    const auto [screenW, screenH] = sys->getScreenSizeWH();
    actualScreen = {0.0f, 0.0f, screenW, screenH };

    const double screenRatio = screenW / screenH, renderRatio = 16.0f/9.0f;

    // screenRatio != renderRatio ?
    if(std::abs(screenRatio - renderRatio) >  std::numeric_limits<double>::epsilon()) {
        if (screenRatio > renderRatio) { // add black bars lateraly
            actualScreen.width = (screenH*16.0f)/9.0f;
            actualScreen.x = screenW / 2 - actualScreen.width / 2;

        } else { // add bars vertically
            actualScreen.height = (screenW*9.0f)/16.0f;
            actualScreen.y = screenH / 2 - actualScreen.height / 2;
        }
    }
}
