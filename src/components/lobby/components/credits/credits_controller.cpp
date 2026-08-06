#include "credits.hpp"

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



    if (IsKeyPressed(KEY_ESCAPE)) {//goto lobby
        return ControllerExitCode::GOTO_LOBBY;
    }

    return ControllerExitCode::CONTINUE;
}
