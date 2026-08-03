#include "lobby.hpp"

ControllerExitCode Lobby::handleModality() {
    if(IsKeyReleased(KEY_DOWN)) {
        this->choice++;
    }
    if(IsKeyReleased(KEY_UP)) {
        this->choice--;
    }
    if(IsKeyReleased(KEY_ENTER)) {// vigile in mutande
        if(this->choice == MenuSelection::TRAINING) {
            this->sys->modalityType = ModalityType::TRAINING;
            return ControllerExitCode::EXITMODALITY;
        }
        if(this->choice == MenuSelection::SURVIVAL) {
            this->sys->modalityType = ModalityType::SURVIVAL;
            return ControllerExitCode::EXITMODALITY;
        }
        if(this->choice == MenuSelection::DUEL) {
            this->sys->modalityType = ModalityType::DUEL;
            return ControllerExitCode::EXITMODALITY;
        }
        if(this->shouldExit()) {
            this->sys->modalityType = ModalityType::NONE;
            this->sys->shutdown = true;
            return ControllerExitCode::EXITMODALITY;
        }

    }

    return ControllerExitCode::NOP;
}
