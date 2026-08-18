#ifndef LOBBYMENU_HPP
#define LOBBYMENU_HPP

// #include "../../../../core/modality.hpp"
// #include "../../../../core/system.hpp"
#include "../../lobby.hpp"
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


class LobbyMenu : public LobbyScreen {
    private:
        MenuSelection choice;

    public:
        LobbyMenu();
        ~LobbyMenu() override = default;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        // ControllerExitCode handleModality() override;
        LobbyState handleLobbySubMode() override;
};


#endif
