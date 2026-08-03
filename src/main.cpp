// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/lobby/lobby.hpp"
// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "components/workinprogress/workinprogress.hpp"

#include <memory>

int main() {
    System *sys = System::getInstance();
    // (init and) keep-alive current modality until explicitly needed
    std::unique_ptr<Modality> mod = std::make_unique<Lobby>(sys);

    while(!sys->shouldExit()) {
        //update audio
        sys->soundManager->updateAudio();

        //controller
        ControllerExitCode cec = mod->handleModality();
        if(cec == ControllerExitCode::EXITMODALITY) {
            // explicitly delete (or else mod will delete at main() ends)
            mod.get()->~Modality();

            switch (sys->modalityType) {
                case ModalityType::LOBBY:
                    mod = std::make_unique<Lobby>(sys);
                    break;
                case ModalityType::TRAINING:
                    mod = std::make_unique<WorkInProgress>(sys); // TODO
                    break;
                case ModalityType::SURVIVAL:
                    mod = std::make_unique<WorkInProgress>(sys); // TODO
                    break;
                case ModalityType::DUEL:
                    mod = std::make_unique<WorkInProgress>(sys); // TODO
                    break;
                default:
                    // ModalityType::NONE -> do nothing
                    break;
            }

        }

        //draw
        BeginDrawing();
        mod->drawModality();
        EndDrawing();
    }

    return 0;
}
