#include "workinprogress.hpp"

ControllerExitCode WorkInProgress::handleModality() {
    if(IsKeyReleased(KEY_ENTER)) {
        sys->modalityType = ModalityType::LOBBY;
        return ControllerExitCode::EXITMODALITY;
    }

    return ControllerExitCode::CONTINUE;
}
