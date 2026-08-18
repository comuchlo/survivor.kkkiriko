#include "lobbymenu.hpp"
#include <cstdio>
#include <raylib.h>

LobbyState LobbyMenu::handleLobbySubMode() {
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        this->choice++;
    }
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        this->choice--;
    }
    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z)) {// vigile in mutande
        switch (this->choice) {
            case MenuSelection::TRAINING:
                return LobbyState::GOTO_TRAINING;
            case MenuSelection::DUEL:
                return LobbyState::GOTO_DUEL;
            case MenuSelection::SURVIVAL:
                return LobbyState::GOTO_SURVIVAL;
            case MenuSelection::SETTINGS:
                return LobbyState::SETTINGS;
            case MenuSelection::HOWTOPLAY:
                return LobbyState::HOWTOPLAY;
            case MenuSelection::CREDITS:
                return LobbyState::CREDITS;
            case MenuSelection::EXIT:
                return LobbyState::SHUTDOWN;
        }
    }

    return LobbyState::CONTINUE_SELF;
}
