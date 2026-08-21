#include "workinprogress.hpp"
#include <raylib.h>

void WorkInProgress::drawModality() {
    const int buttonFont= drawer->buttonFontSize, subTitleFont= drawer->subTitleFontSize;

    // background image
    DrawTexture(backgroundImage, 0, 0, WHITE); // render is same res as image

    // "work in progress"
    drawer->drawTextSFC(
        "Work in progress",
        50,
        subTitleFont,
        RED,
        BLACK,
        BLACK
    );

    // "return to lobby"
    drawer->drawTextSFC(
        "return to lobby",
        552,
        buttonFont,
        BLACK,
        BLACK,
        RED
    );

}
