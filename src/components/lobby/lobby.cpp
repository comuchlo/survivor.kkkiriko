#include "lobby.hpp"
#include "components/lobbymenu/lobbymenu.hpp"
#include <cstdio>
#include <memory>
#include <raylib.h>

Lobby::Lobby() {

    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    backgroundImage = drawer->getLobbyBgTexture();

    lobbyModality = std::make_unique<LobbyMenu>();
}

LobbyScreen::LobbyScreen(Texture2D* backgroundImage) {
    this->backgroundImage= backgroundImage;
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
}
LobbyScreen::LobbyScreen() {
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
    this->backgroundImage= this->drawer->getLobbyBgTexture();
}
