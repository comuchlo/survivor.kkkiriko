#ifndef MODALITY_HPP
#define MODALITY_HPP

enum class ModalityType {
    NONE = 0,
    LOBBY = 1,
    TRAINING = 2,
    DUEL = 3,
    SURVIVAL = 4,
    SETTINGS = 5,
    HOWTOPLAY = 6,
    CREDITS = 7,
    EXIT = 8,
};

enum class ControllerExitCode {
    // CONTINUE = 0,
    // EXITMODALITY = 1,
    GOTO_LOBBY = 0,
    GOTO_LOBBY_SETTINGS = 1,
    GOTO_LOBBY_HOWTOPLAY = 2,
    GOTO_LOBBY_CREDITS = 3,
    GOTO_TRAINING = 4,
    GOTO_TRAINING_PAUSE = 5,
    GOTO_TRAINING_SETTINGS = 6,
    GOTO_SURVIVAL = 7,
    GOTO_SURVIVAL_PAUSE = 8,
    GOTO_SURVIVAL_SETTINGS = 9,
    GOTO_DUEL = 10,
    GOTO_DUEL_PAUSE = 11,
    GOTO_DUEL_SETTINGS = 12,
    CONTINUE = 13,
    SHUTDOWN = 14,
};

class Modality {// define general class to hold lobby, training, duel, survival
    public:
        ModalityType modalityType;

        Modality();
        virtual ~Modality();

        virtual void drawModality();
        virtual void drawEndModality();

        virtual ControllerExitCode handleModality();
};

#endif
