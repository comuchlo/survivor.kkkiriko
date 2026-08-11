// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/lobby/lobby.hpp"
// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/workinprogress/workinprogress.hpp"
#include "core/draw_manager.hpp"
#include "core/game_manager.hpp"
#include "core/modality.hpp"
#include "core/system.hpp"
#include <cstdio>
#include <memory>
#include <raylib.h>

int main() {
    ControllerExitCode cec;

    // keep-alive essentials
    System* sys = System::getInstance();
    DrawManager* draw_manager = DrawManager::getInstance();
    GameManager* game_manager = GameManager::getInstance();

    while(!sys->shouldExit()) {
        // every-frame-updates
        sys->soundManager->updateAudio();
        game_manager->update();

        // conditional updates
        if(IsWindowResized()) {
            sys->update();
            draw_manager->update();
        }

        //runs logic
        cec = game_manager->mode->handleModality();

        //draw
        BeginDrawing();
            ClearBackground(BLACK);

            //all drawing goes into render
            BeginTextureMode(draw_manager->render);
                ClearBackground(BLACK);
                game_manager->mode->drawModality();
            EndTextureMode();

            //draw render based on current screen
            draw_manager->drawRender();

        EndDrawing();

        //controller
        if(cec != ControllerExitCode::CONTINUE) {
            // game_manager->mode.reset();

            if(cec < ControllerExitCode::GOTO_TRAINING) { // lobby modalities
                game_manager->mode = std::make_unique<Lobby>();

            } else if(cec < ControllerExitCode::GOTO_SURVIVAL) { // training modalities
                game_manager->mode = std::make_unique<WorkInProgress>();

            } else if (cec < ControllerExitCode::GOTO_DUEL) { // survival modalities
                game_manager->mode = std::make_unique<WorkInProgress>();

            } else if (cec < ControllerExitCode::CONTINUE) { // duel modalities
                game_manager->mode = std::make_unique<WorkInProgress>();

            } else if (cec == ControllerExitCode::SHUTDOWN) { // shutdown
                sys->shutDown();

            }
        }
    }

    return 0;
}
