#include "lobby.hpp"

#include "components/lobbymenu/lobbymenu.hpp"
#include "components/settings/settings.hpp"
#include "components/howtoplay/howtoplay.hpp"
#include "components/credits/credits.hpp"

#include <cstdio>
#include <memory>

ControllerExitCode Lobby::handleModality() {
    const LobbyState lobby_state = lobbyModality->handleLobbySubMode();

        switch (lobby_state) {
            case LobbyState::MENU:
                lobbyModality = std::make_unique<LobbyMenu>();
                break;
            case LobbyState::SETTINGS:
                lobbyModality = std::make_unique<Settings>();
                break;
            case LobbyState::HOWTOPLAY:
                lobbyModality = std::make_unique<HowToPlay>();
                break;
            case LobbyState::CREDITS:
                lobbyModality = std::make_unique<Credits>();
                break;
            case LobbyState::GOTO_SURVIVAL:
                return ControllerExitCode::GOTO_SURVIVAL;
            case LobbyState::GOTO_DUEL:
                return ControllerExitCode::GOTO_DUEL;
            case LobbyState::GOTO_TRAINING:
                return ControllerExitCode::GOTO_TRAINING;
            case LobbyState::SHUTDOWN:
                return ControllerExitCode::SHUTDOWN;
            case LobbyState::CONTINUE_SELF:
                return ControllerExitCode::CONTINUE;
        }

    return ControllerExitCode::CONTINUE;
}
