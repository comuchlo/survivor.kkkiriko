#include "workinprogress.hpp"
#include <raylib.h>

void WorkInProgress::drawModality() {
    auto [renderWidth, renderHeight]= this->sys->getRenderSizeWH();
    RenderTexture render = sys->render;
    const int titleFont= this->sys->titlefontSize, buttonFont= this->sys->buttonFontSize, subTitleFont= this->sys->subTitleFontSize;

    BeginTextureMode(render);
    ClearBackground(BLACK);

    // background image
    DrawTexture(this->backgroundImage, 0, 0, WHITE); // render is same res as image
    // "work in progress"
    this->drawer->drawTextSF(
        "Work in progress",
        (renderWidth / 2) - ((float)MeasureText("Work in progress", subTitleFont) / 2) + 2,
        50,
        subTitleFont,
        RED,
        BLACK,
        BLACK
    );

    // "return to lobby"
    this->drawer->drawTextSF(
        "return to lobby",
        (renderWidth / 2) - ((float)MeasureText("Work in progress", buttonFont) / 2) + 2,
        552,
        buttonFont,
        BLACK,
        BLACK,
        RED
    );

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
