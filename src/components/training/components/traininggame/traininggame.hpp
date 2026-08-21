#ifndef TRAININGGAME_HPP
#define TRAININGGAME_HPP

#include "../../../../core/game_manager.hpp"
#include "../../training.hpp"
#include <raylib.h>

class TrainingGame : public TrainingModality {
    // N.B.: protected:
    //     System* sys;
    //     DrawManager* drawer;
    //     Texture2D* trainingMap;
    private:
        GameManager* game_manager;
    public:
        TrainingGame(Texture2D* trainingMap);
        ~TrainingGame() override = default;

        TrainingState handleTrainingSubMode() override;
        void drawModality() override;
};

#endif
