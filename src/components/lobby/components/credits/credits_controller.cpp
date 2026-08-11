#include "credits.hpp"
#include <raylib.h>

ControllerExitCode Credits::handleModality() {
    // CHECK INPUT
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {//goto lobby
        return ControllerExitCode::GOTO_LOBBY;
    }
    autoscroll_speed = (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) ?
        MAX_AUTOSCROLL_SPEED : DEF_AUTOSCROLL_SPEED;


    // UPDATE
    // translate 2D coord to screen coord of the last text
    float creditsHEndByScreen = GetWorldToScreen2D(
        {0.0f, CREDITS_HEIGHT_END+(float)sys->titlefontSize/2}, //center of the final text
        game_manager->camera1
    ).y;

    if(creditsHEndByScreen > 0) {
        const float autoScroll = autoscroll_speed * game_manager->getDeltaTime();

        // update
        game_manager->camera1.offset.y -= autoScroll;

        // if center of screen -> block
        if(creditsHEndByScreen <= (float)drawer->RENDER_HEIGHT/2)
            stoppedLastText = true;

    } else {
        endedAutoScrool = true;
    }

    return ControllerExitCode::CONTINUE;
}
