#ifndef LOBBY_HPP
#define LOBBY_HPP

// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "../../core/draw_manager.hpp"

enum class MenuSelection{
    TRAINING = 1,
    DUEL = 2,
    SURVIVAL = 3,
    SETTINGS = 4,
    HOWTOPLAY = 5,
    CREDITS = 6,
    EXIT = 7,
};

MenuSelection& operator++(MenuSelection& val);
MenuSelection  operator++(MenuSelection& val, int);

MenuSelection& operator--(MenuSelection& val);
MenuSelection  operator--(MenuSelection& val, int);


class Lobby : public Modality {
    private:
        MenuSelection choice;
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
        bool shouldExit() override;
};

#endif
