// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/lobby/lobby.hpp"
// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/workinprogress/workinprogress.hpp"
#include "core/game_manager.hpp"
#include "core/modality.hpp"
#include "core/system.hpp"
#include <cstdio>
#include <memory>

int main() {
    ControllerExitCode cec;

    // keep-alive essentials
    System* sys = System::getInstance();
    GameManager* game_manager = GameManager::getInstance();

    while(!sys->shouldExit()) {
        //update
        sys->soundManager->updateAudio();
        game_manager->update();

        //runs logic
        cec = game_manager->mode->handleModality();

        //draw
        BeginDrawing();
        game_manager->mode->drawModality();
        EndDrawing();


        //controller
        if(cec != ControllerExitCode::CONTINUE) {

            if(cec < ControllerExitCode::GOTO_TRAINING) { // lobby modalities
                game_manager->mode = std::make_unique<Lobby>();

            } else if(cec < ControllerExitCode::GOTO_SURVIVAL) { // training modalities
                printf("const char *__restrict  _Nonnull format, ...\n\n");
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
