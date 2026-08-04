#include "lobby.hpp"

ControllerExitCode Lobby::handleModality() {

    if(IsKeyReleased(KEY_DOWN)) {
        this->choice++;
    }
    if(IsKeyReleased(KEY_UP)) {
        this->choice--;
    }
    if(IsKeyReleased(KEY_ENTER)) {// vigile in mutande
        switch (this->choice) {
            case MenuSelection::TRAINING:
                this->sys->modalityType = ModalityType::TRAINING;
                break;
            case MenuSelection::SURVIVAL:
                this->sys->modalityType = ModalityType::SURVIVAL;
                break;
            case MenuSelection::DUEL:
                this->sys->modalityType = ModalityType::DUEL;
                break;
            case MenuSelection::SETTINGS:
                this->sys->modalityType = ModalityType::SETTINGS;
                break;
            case MenuSelection::HOWTOPLAY:
                this->sys->modalityType = ModalityType::HOWTOPLAY;
                break;
            case MenuSelection::CREDITS:
                this->sys->modalityType = ModalityType::CREDITS;
                break;
            case MenuSelection::EXIT:
                this->sys->modalityType = ModalityType::NONE;
                this->sys->shutdown = true;
                break;
        }
        return ControllerExitCode::EXITMODALITY;
    }

    return ControllerExitCode::CONTINUE;
}
