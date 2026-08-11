#include "workinprogress.hpp"
#include <raylib.h>

ControllerExitCode WorkInProgress::handleModality() {
    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {
        return ControllerExitCode::GOTO_LOBBY;
    }

    return ControllerExitCode::CONTINUE;
}
