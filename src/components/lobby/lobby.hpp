#ifndef LOBBY_HPP
#define LOBBY_HPP

// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "../../core/draw_manager.hpp"
#include <memory>
#include <raylib.h>


enum class LobbyState{
    MENU = 1,
    SETTINGS,
    HOWTOPLAY,
    CREDITS,
    GOTO_TRAINING,
    GOTO_SURVIVAL,
    GOTO_DUEL,
    CONTINUE_SELF,
    SHUTDOWN,
};

class LobbyScreen{
    protected:
        System* sys;
        DrawManager* drawer;
        Texture2D* backgroundImage;
    public:
        explicit LobbyScreen(Texture2D*);
        LobbyScreen();
        virtual ~LobbyScreen() = default;

        virtual LobbyState handleLobbySubMode()=0;
        virtual void drawModality()=0;
};

class Lobby : public Modality {
    private:
        System* sys;
        DrawManager* drawer;
        Texture2D* backgroundImage;

    public:

        Lobby();
        ~Lobby() override = default;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        ControllerExitCode handleModality() override;


        std::unique_ptr<LobbyScreen> lobbyModality;
};


#endif
