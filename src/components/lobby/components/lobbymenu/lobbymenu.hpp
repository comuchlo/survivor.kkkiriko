#ifndef LOBBYMENU_HPP
#define LOBBYMENU_HPP

// #include "../../../../core/modality.hpp"
// #include "../../../../core/system.hpp"
#include "../../../../core/draw_manager.hpp"
#include <raylib.h>

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


class LobbyMenu : public Modality {
    private:
        MenuSelection choice;
        System* sys;
        DrawManager* drawer;
        Texture2D* backgroundImage; //shared from parent

    public:
        LobbyMenu(Texture2D* backgroundImage);
        ~LobbyMenu() override;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        ControllerExitCode handleModality() override;
};


#endif
