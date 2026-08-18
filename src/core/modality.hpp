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
    // ok ormai per la lobby ma il riesto pls gestiamolo internamente nel component
    // con un propio enum e logica, senza dover fare un cambio di contesto e passando comunque
    // per il main, non con un'ulteriore astrazione che confonde i livelli di gestione usando
    // un enum globale per una gestione locale come nella lobby
    GOTO_LOBBY = 0,
    // GOTO_LOBBY_SETTINGS = 1,
    // GOTO_LOBBY_HOWTOPLAY = 2,
    // GOTO_LOBBY_CREDITS = 3,
    GOTO_TRAINING = 4,
    GOTO_SURVIVAL = 5,
    GOTO_DUEL = 6,
    CONTINUE = 7,
    SHUTDOWN = 8,
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
