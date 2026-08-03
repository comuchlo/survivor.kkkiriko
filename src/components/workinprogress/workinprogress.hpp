#ifndef WORKINPROGRESS_HPP
#define WORKINPROGRESS_HPP

// includes also "system.hpp" {"soundmanager.hpp" { <raylib.h> }, "modality.hpp"}
#include "../../core/draw_manager.hpp"

class WorkInProgress : public Modality {
    private:
        System* sys;
        DrawManager* drawer;
        Texture2D backgroundImage;

    public:
        WorkInProgress(System* sys);
        ~WorkInProgress() override;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        ControllerExitCode handleModality() override;
        bool shouldExit() override;
};

#endif
