#ifndef HOWTOPLAY_HPP
#define HOWTOPLAY_HPP

#include "../../../../core/game_manager.hpp"
#include "../../lobby.hpp"


class HowToPlay : public LobbyScreen {
    protected:
        GameManager* game_manager;
    public:
        HowToPlay();
        ~HowToPlay() override = default;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        // ControllerExitCode handleModality() override;
        LobbyState handleLobbySubMode() override;
};


#endif
