#include "credits.hpp"
#include <raylib.h>

ControllerExitCode Credits::handleModality() {
    float* camera1y = &this->game_manager->camera1.offset.y;

    if((*camera1y) > -this->CREDITS_HEIGHT_END) {
        const float autoScroll = this->AUTOSCROLL_SPEED * this->game_manager->getDeltaTime();

        // update
        (*camera1y) -= autoScroll;

        // shiftdown only "thanks for playing" it has reached half of the render
        if((*camera1y)< -(float)this->CREDITS_HEIGHT_END+((float)this->sys->render.texture.height/2)) {
            this->shiftDown+=autoScroll;
        }
    } else {
        endedAutoScrool = true;
    }



    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {//goto lobby
        return ControllerExitCode::GOTO_LOBBY;
    }

    return ControllerExitCode::CONTINUE;
}
