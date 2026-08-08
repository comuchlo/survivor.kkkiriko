#include "lobby.hpp"

#include "components/lobbymenu/lobbymenu.hpp"
#include "components/settings/settings.hpp"
#include "components/howtoplay/howtoplay.hpp"
#include "components/credits/credits.hpp"

#include <memory>

ControllerExitCode Lobby::handleModality() {
    const ControllerExitCode cec = this->lobbyModality->handleModality();

    switch (cec) {
        case ControllerExitCode::GOTO_LOBBY:// this controller can handle request
            this->lobbyModality = std::make_unique<LobbyMenu>(&this->backgroundImage);
            break;
        case ControllerExitCode::GOTO_LOBBY_SETTINGS:
            this->lobbyModality = std::make_unique<Settings>(&this->backgroundImage);
            break;
        case ControllerExitCode::GOTO_LOBBY_HOWTOPLAY:
            this->lobbyModality = std::make_unique<HowToPlay>(&this->backgroundImage);
            break;
        case ControllerExitCode::GOTO_LOBBY_CREDITS:
            this->lobbyModality = std::make_unique<Credits>(&this->backgroundImage);
            break;
        default: // can't handle request: forward it
            return cec;
    }

    return ControllerExitCode::CONTINUE;
}
