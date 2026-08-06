#ifndef LOBBY_HPP
#define LOBBY_HPP

// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "../../core/draw_manager.hpp"
#include <memory>

class Lobby : public Modality {
    private:
        System* sys;
        DrawManager* drawer;
        Texture2D backgroundImage;

    public:
        Lobby();
        ~Lobby() override;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        ControllerExitCode handleModality() override;

        std::unique_ptr<Modality> lobbyModality;
};

#endif
