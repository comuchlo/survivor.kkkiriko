#include "lobby.hpp"

#include "components/lobbymenu/lobbymenu.hpp"
#include "components/settings/settings.hpp"
#include "components/howtoplay/howtoplay.hpp"
#include "components/credits/credits.hpp"

#include <memory>

ControllerExitCode Lobby::handleModality() {
    const ControllerExitCode cec = lobbyModality->handleModality();

    switch (cec) {
        case ControllerExitCode::GOTO_LOBBY:// ontroller can handle request
            // lobbyModality.reset();
            lobbyModality = std::make_unique<LobbyMenu>(&backgroundImage);
            break;
        case ControllerExitCode::GOTO_LOBBY_SETTINGS:
            // lobbyModality.reset();
            lobbyModality = std::make_unique<Settings>(&backgroundImage);
            break;
        case ControllerExitCode::GOTO_LOBBY_HOWTOPLAY:
            // lobbyModality.reset();
            lobbyModality = std::make_unique<HowToPlay>(&backgroundImage);
            break;
        case ControllerExitCode::GOTO_LOBBY_CREDITS:
            // lobbyModality.reset();
            lobbyModality = std::make_unique<Credits>(&backgroundImage);
            break;
        default: // can't handle request: forward it
            return cec;
    }

    return ControllerExitCode::CONTINUE;
}
