#include "credits.hpp"

ControllerExitCode Credits::handleModality() {
    float* camera1y = &game_manager->camera1.offset.y;

    if((*camera1y) > -CREDITS_HEIGHT_END) {
        const float autoScroll = AUTOSCROLL_SPEED * game_manager->getDeltaTime();

        // update
        (*camera1y) -= autoScroll;

        // shiftdown only "thanks for playing" it has reached half of the render
        if((*camera1y)< -(float)CREDITS_HEIGHT_END+((float)drawer->RENDER_HEIGHT/2)) {
            shiftDown+=autoScroll;
        }
    } else {
        endedAutoScrool = true;
    }



    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {//goto lobby
        return ControllerExitCode::GOTO_LOBBY;
    }

    return ControllerExitCode::CONTINUE;
}
