#include "../../core/system.hpp"
#include "../../core/draw_manager.hpp"

#ifndef LOBBY_HPP
#define LOBBY_HPP


enum class MenuSelection{
    TRAINING = 1,
    DUEL = 2,
    SURVIVAL = 3,
    SETTINGS = 4,
    HOWTOPLAY = 5,
    CREDITS = 6,
    EXIT = 7,
};


class Lobby{
    private:
        MenuSelection choice= MenuSelection::TRAINING;
        System* sys= System::getInstance();
        DrawManager* drawer= DrawManager::getInstance();
    public:
        void drawLobby();
        bool shouldExit();
};

#endif
