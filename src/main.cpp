// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/lobby/lobby.hpp"
#include "components/survival/survival.hpp"
// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/training/training.hpp"
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
        game_manager->updateTime();

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
            BeginTextureMode(*draw_manager->currRender());
                ClearBackground(BLACK);
                game_manager->mode->drawModality();
            EndTextureMode();

            //draw render based on current screen
            draw_manager->drawRender();

        EndDrawing();


        //controller
        if(cec != ControllerExitCode::CONTINUE) {

            switch (cec) {
                case ControllerExitCode::GOTO_LOBBY:
                    game_manager->mode = std::make_unique<Lobby>();
                    break;
                case ControllerExitCode::GOTO_DUEL:
                    game_manager->mode = std::make_unique<WorkInProgress>();
                    break;

                case ControllerExitCode::GOTO_TRAINING:
                    game_manager->mode = std::make_unique<Training>();
                    break;

                case ControllerExitCode::GOTO_SURVIVAL:
                    game_manager->mode = std::make_unique<Survival>();
                    break;

                case ControllerExitCode::SHUTDOWN:
                    sys->shutDown();
                    break;

                default:
                    game_manager->mode = std::make_unique<Lobby>();
                    break;
            }

        }
    }

    return 0;
}
