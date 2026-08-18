#ifndef CREDITS_HPP
#define CREDITS_HPP

#include "../../../../core/game_manager.hpp"
#include "../../lobby.hpp"

class Credits : public LobbyScreen {
    private:
        static const int DEF_AUTOSCROLL_SPEED = 80, MAX_AUTOSCROLL_SPEED = 320,
            CREDITS_HEIGHT_END = 1100;
        int autoscroll_speed;
        bool endedAutoScrool, stoppedLastText;

        GameManager* game_manager;

    public:
        Credits();
        ~Credits() override= default;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        // ControllerExitCode handleModality() override;
        LobbyState handleLobbySubMode() override;
};


#endif
