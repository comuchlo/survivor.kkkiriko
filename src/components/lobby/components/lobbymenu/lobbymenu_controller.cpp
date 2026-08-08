#include "lobbymenu.hpp"
#include <cstdio>
#include <raylib.h>

ControllerExitCode LobbyMenu::handleModality() {

    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        this->choice++;
    }
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        this->choice--;
    }
    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) {// vigile in mutande
        switch (this->choice) {
            case MenuSelection::TRAINING:
                return ControllerExitCode::GOTO_TRAINING;
            case MenuSelection::SURVIVAL:
                printf("SEX \n\n");
                return ControllerExitCode::GOTO_SURVIVAL;
            case MenuSelection::DUEL:
                return ControllerExitCode::GOTO_DUEL;
            case MenuSelection::SETTINGS:
                return ControllerExitCode::GOTO_LOBBY_SETTINGS;
            case MenuSelection::HOWTOPLAY:
                return ControllerExitCode::GOTO_LOBBY_HOWTOPLAY;
            case MenuSelection::CREDITS:
                return ControllerExitCode::GOTO_LOBBY_CREDITS;
            case MenuSelection::EXIT:
                return ControllerExitCode::SHUTDOWN;
        }
    }

    return ControllerExitCode::CONTINUE;
}
