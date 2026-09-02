#ifndef TRAININGMENU_HPP
#define TRAININGMENU_HPP

#include "../../../../core/game_manager.hpp"
#include "../../training.hpp"

enum class TrainingMenuMacroSelection {
    GENERAL = 0,
    PLAYER = 1,
    ENEMY = 2,
};

enum class SettingModSelection {
    INDEX = 0, // important
    MASTERVOLUME = 1,
    MUSICVOLUME = 2,
    EFFECTSVOLUME = 3,
    RESETAUDIO = 4,
    DISPLAYMODE = 5,
    RESOLUTION = 6,
    FPS = 7,
    VSYNC = 8,
    RESETVIDEO = 9,
    RESUME = 10,
    EXIT = 11,
};

enum class PlayerModSelection { // enumerate player stats that are modifiable
    INDEX = 0, // important
    SKIN = 1,
    HP = 2,
    STRENGHT = 3,
    MOVEMENT_SPEED = 4,
    ATTACK_SPEED = 5,
    DIMENSION = 6,
    ULT = 7,
    RESUME = 8,
    EXIT = 9,
};

enum class EnemyModSelection { // enumerate player stats that are modifiable
    INDEX = 0, // important
    TYPE = 1,
    GENERATION_CRITERIA = 2,
    HP = 3,
    STRENGHT = 4,
    MOVEMENT_SPEED = 5,
    ATTACK_SPEED = 6,
    DIMENSION = 7,
    BEHAVIOUR = 8,
    RESUME = 9,
    EXIT = 10,
};

SettingModSelection& operator++(SettingModSelection& val);
SettingModSelection  operator++(SettingModSelection& val, int);
SettingModSelection& operator--(SettingModSelection& val);
SettingModSelection  operator--(SettingModSelection& val, int);

TrainingMenuMacroSelection& operator++(TrainingMenuMacroSelection& val);
TrainingMenuMacroSelection  operator++(TrainingMenuMacroSelection& val, int);
TrainingMenuMacroSelection& operator--(TrainingMenuMacroSelection& val);
TrainingMenuMacroSelection  operator--(TrainingMenuMacroSelection& val, int);

PlayerModSelection& operator++(PlayerModSelection& val);
PlayerModSelection  operator++(PlayerModSelection& val, int);
PlayerModSelection& operator--(PlayerModSelection& val);
PlayerModSelection  operator--(PlayerModSelection& val, int);

EnemyModSelection& operator++(EnemyModSelection& val);
EnemyModSelection  operator++(EnemyModSelection& val, int);
EnemyModSelection& operator--(EnemyModSelection& val);
EnemyModSelection  operator--(EnemyModSelection& val, int);

class TrainingMenu : public TrainingModality {
    // N.B.: protected:
    //     System* sys;
    //     DrawManager* drawer;
    //     Texture2D* trainingMap;
    private:
        GameManager* game_manager;

        TrainingMenuMacroSelection macroSelection;
        SettingModSelection choiceOnGeneral;
        PlayerModSelection choiceOnPlayer;
        EnemyModSelection choiceOnEnemy;

    public:
        TrainingMenu();
        ~TrainingMenu() override = default;

        TrainingState handleTrainingSubMode() override;
        void drawModality() override;
};

#endif
