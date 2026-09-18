#include "credits.hpp"
#include <raylib.h>

LobbyState Credits::handleLobbySubMode() {
    // CHECK INPUT
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {//goto lobby
        return LobbyState::MENU;
    }
    autoscroll_speed = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) ?
        MAX_AUTOSCROLL_SPEED : DEF_AUTOSCROLL_SPEED;


    // UPDATE
    // translate 2D coord to screen coord of the last text
    float creditsHEndByScreen = GetWorldToScreen2D(
        {0.0f, CREDITS_HEIGHT_END+(float)drawer->titleFontSize/2}, //center of the final text
        game_manager->cameras[0]
    ).y;

    if(creditsHEndByScreen > 0) {
        const float autoScroll = autoscroll_speed * game_manager->getDeltaTime();

        // update
        game_manager->cameras[0].offset.y -= autoScroll;

        // if center of screen -> block
        if(creditsHEndByScreen <= (float)drawer->RENDER_HEIGHT/2)
            stoppedLastText = true;

    } else {
        endedAutoScrool = true;
    }

    return LobbyState::CONTINUE_SELF;
}
