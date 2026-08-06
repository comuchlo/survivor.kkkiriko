#include "lobbymenu.hpp"
#include <raylib.h>

ControllerExitCode LobbyMenu::handleModality() {

    if(IsKeyPressed(KEY_DOWN)) {
        this->choice++;
    }
    if(IsKeyPressed(KEY_UP)) {
        this->choice--;
    }
    if(IsKeyPressed(KEY_ENTER)) {// vigile in mutande
        switch (this->choice) {
            case MenuSelection::TRAINING:
                return ControllerExitCode::GOTO_TRAINING;
                break;
            case MenuSelection::SURVIVAL:
                return ControllerExitCode::GOTO_SURVIVAL;
                break;
            case MenuSelection::DUEL:
                return ControllerExitCode::GOTO_DUEL;
                break;
            case MenuSelection::SETTINGS:
                return ControllerExitCode::GOTO_LOBBY_SETTINGS;
                break;
            case MenuSelection::HOWTOPLAY:
                return ControllerExitCode::GOTO_LOBBY_HOWTOPLAY;
                break;
            case MenuSelection::CREDITS:
                return ControllerExitCode::GOTO_LOBBY_CREDITS;
                break;
            case MenuSelection::EXIT:
                return ControllerExitCode::SHUTDOWN;
                break;
        }
    }

    return ControllerExitCode::CONTINUE;
}
