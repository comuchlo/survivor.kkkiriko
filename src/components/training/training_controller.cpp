#include "training.hpp"

#include "components/traininggame/traininggame.hpp"
#include "components/trainingmenu/trainingmenu.hpp"

#include <cstdio>
#include <memory>

ControllerExitCode Training::handleModality() {
    const TrainingState lobby_state = trainingModality->handleTrainingSubMode();

        switch (lobby_state) {
            case TrainingState::IN_GAME:
                trainingModality = std::make_unique<TrainingGame>(&trainingMap);
                break;
            case TrainingState::TRAINING_PAUSE_MENU:
                trainingModality = std::make_unique<TrainingMenu>();
                break;
            case TrainingState::GOTO_LOBBY:
                return ControllerExitCode::GOTO_LOBBY;
            case TrainingState::CONTINUE:
                return ControllerExitCode::CONTINUE;
        }

    return ControllerExitCode::CONTINUE;
}
