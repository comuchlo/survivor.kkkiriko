#include "howtoplay.hpp"
#include <algorithm>
#include <raylib.h>


ControllerExitCode HowToPlay::handleModality() {
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {//up
        this->game_manager->camera1.offset.y = std::max(
            this->game_manager->camera1.offset.y-5, 0.0f
        );
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {//down
        this->game_manager->camera1.offset.y = std::min(
            this->game_manager->camera1.offset.y+5, 1000.0f - this->sys->render.texture.height
        );
    }
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {//confirm
        return ControllerExitCode::GOTO_LOBBY;
    }

    return ControllerExitCode::CONTINUE;
}
