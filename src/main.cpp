// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/lobby/lobby.hpp"
// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/workinprogress/workinprogress.hpp"
#include "core/game_manager.hpp"
#include "core/modality.hpp"
#include <cstdio>

int main() {
    System *sys = System::getInstance();
    sys->cec=ControllerExitCode::CONTINUE;
    sys->modalityType=ModalityType::LOBBY;
    // (init and) keep-alive current modality until explicitly needed
    GameManager *game_manager= GameManager::getInstance();
    game_manager->mode= new Lobby();


    while(!sys->shouldExit()) {
        //update audio
        sys->soundManager->updateAudio();
        //runs logic
        sys->cec= game_manager->mode->handleModality();
        //draw
        BeginDrawing();
        game_manager->mode->drawModality();
        EndDrawing();

        //controller
        if(sys->cec == ControllerExitCode::EXITMODALITY) { // resets mode and starts another
            // explicitly delete (or else mod will delete at main() ends)
            game_manager->mode->~Modality();

            switch (sys->modalityType) {
                case ModalityType::LOBBY:
                    game_manager->mode = new Lobby();
                    break;
                case ModalityType::TRAINING:
                    game_manager->mode= new WorkInProgress(); // TODO
                    break;
                case ModalityType::DUEL:
                    game_manager->mode= new WorkInProgress(); // TODO
                    break;
                case ModalityType::SURVIVAL:
                    game_manager->mode= new WorkInProgress(); // TODO
                    break;
                case ModalityType::SETTINGS:
                    game_manager->mode= new WorkInProgress(); // TODO
                    break;
                case ModalityType::HOWTOPLAY:
                    game_manager->mode= new WorkInProgress(); // TODO
                    break;
                case ModalityType::CREDITS:
                    game_manager->mode= new WorkInProgress(); // TODO
                    break;
                case ModalityType::EXIT:
                    sys->shutdown = true;
                    break;
                default: //ModalityType::NONE
                    game_manager->mode = new Lobby();
                    break;
            }
        }
        sys->cec= ControllerExitCode::CONTINUE; // re-establishes the loop
    }

    return 0;
}
