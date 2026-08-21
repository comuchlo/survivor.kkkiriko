#ifndef TRAININGMENU_HPP
#define TRAININGMENU_HPP

#include "../../../../core/game_manager.hpp"
#include "../../training.hpp"

class TrainingMenu : public TrainingModality {
    // N.B.: protected:
    //     System* sys;
    //     DrawManager* drawer;
    //     Texture2D* trainingMap;
    private:
        GameManager* game_manager;
    public:
        TrainingMenu();
        ~TrainingMenu() override = default;

        TrainingState handleTrainingSubMode() override;
        void drawModality() override;
};

#endif
