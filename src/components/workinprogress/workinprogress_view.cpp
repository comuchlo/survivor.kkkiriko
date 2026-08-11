#include "workinprogress.hpp"
#include <raylib.h>

void WorkInProgress::drawModality() {
    const float renderWidth = drawer->RENDER_WIDTH, renderHeight = drawer->RENDER_HEIGHT;
    const int titleFont= sys->titlefontSize, buttonFont= sys->buttonFontSize,
        subTitleFont= sys->subTitleFontSize;


    // background image
    DrawTexture(backgroundImage, 0, 0, WHITE); // render is same res as image

    // "work in progress"
    drawer->drawTextSF(
        "Work in progress",
        (renderWidth / 2) - ((float)MeasureText("Work in progress", subTitleFont) / 2) + 2,
        50,
        subTitleFont,
        RED,
        BLACK,
        BLACK
    );

    // "return to lobby"
    drawer->drawTextSF(
        "return to lobby",
        (renderWidth / 2) - ((float)MeasureText("Work in progress", buttonFont) / 2) + 2,
        552,
        buttonFont,
        BLACK,
        BLACK,
        RED
    );

}
