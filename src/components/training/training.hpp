#ifndef TRAINING_HPP
#define TRAINING_HPP

// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "../../core/draw_manager.hpp"
#include "../../core/game_manager.hpp"
#include <memory>
#include <raylib.h>


enum class TrainingState {
    IN_GAME = 0,
    TRAINING_PAUSE_MENU = 1,
    CONTINUE = 2,
    GOTO_LOBBY = 3,
};

class TrainingModality {
    protected:
        System* sys;
        DrawManager* drawer;
        Texture2D* trainingMap;
    public:
        explicit TrainingModality(Texture2D*);
        TrainingModality();
        virtual ~TrainingModality() = default;

        virtual TrainingState handleTrainingSubMode() = 0;
        virtual void drawModality() = 0;
};

class Training : public Modality {
    private:
        System* sys;
        DrawManager* drawer;
        GameManager* game_manager;
        Texture2D trainingMap;

    public:
        Training();
        ~Training() override;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        ControllerExitCode handleModality() override;


        std::unique_ptr<TrainingModality> trainingModality;
};


#endif
