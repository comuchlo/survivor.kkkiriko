#include "lobby.hpp"
#include "components/lobbymenu/lobbymenu.hpp"
#include <memory>

Lobby::Lobby() {
    this->sys = System::getInstance();
    this->drawer = DrawManager::getInstance();
    this->backgroundImage = LoadTexture("./textures/kirikobg2.png");
    this->lobbyModality = std::make_unique<LobbyMenu>(&this->backgroundImage);
}

Lobby::~Lobby() {
    // this->lobbyModality.~Modality(); // no heap resources actually
    UnloadTexture(this->backgroundImage);
}
