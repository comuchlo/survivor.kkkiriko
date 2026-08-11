#include "lobby.hpp"
#include "components/lobbymenu/lobbymenu.hpp"
#include <memory>

Lobby::Lobby() {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    backgroundImage = LoadTexture("./textures/kirikobg2.png");
    lobbyModality = std::make_unique<LobbyMenu>(&backgroundImage);
}

Lobby::~Lobby() {
    // lobbyModality.~Modality(); // no heap resources actually
    UnloadTexture(backgroundImage);
}
