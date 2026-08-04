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
    CREDITS = 6,
};

enum class ControllerExitCode {
    CONTINUE = 0,
    EXITMODALITY = 1,
};

class Modality {// define general class to hold lobby, training, duel, survival
    public:
        ModalityType modalityType;

        Modality();
        virtual ~Modality();

        virtual void drawModality();
        virtual void drawEndModality();

        virtual ControllerExitCode handleModality();

        virtual bool shouldExit();

};

#endif
