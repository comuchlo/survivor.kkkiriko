#include "howtoplay.hpp"
#include <algorithm>
#include <raylib.h>


LobbyState HowToPlay::handleLobbySubMode() {
    const float SCROLL = 0.1f;

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {//up
        game_manager->cameras[0].offset.y = std::max(
            game_manager->cameras[0].offset.y-(SCROLL*game_manager->getDeltaTime()),
            0.0f
        );
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {//down
        game_manager->cameras[0].offset.y = std::min(
            game_manager->cameras[0].offset.y+(SCROLL*game_manager->getDeltaTime()),
            1000.0f - drawer->RENDER_HEIGHT
        );
    }
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {//confirm
        return LobbyState::MENU;
    }

    return LobbyState::CONTINUE_SELF ;
}
