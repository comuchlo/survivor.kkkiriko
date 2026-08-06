#include "workinprogress.hpp"
#include <raylib.h>

ControllerExitCode WorkInProgress::handleModality() {
    if(IsKeyPressed(KEY_ENTER)) {
        return ControllerExitCode::GOTO_LOBBY;
    }

    return ControllerExitCode::CONTINUE;
}
