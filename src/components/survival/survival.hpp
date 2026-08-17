#ifndef SURVIVAL_HPP
#define SURVIVAL_HPP

#include "../../core/draw_manager.hpp"
#include "../../game_elements/player.hpp"
#include <raylib.h>


enum class SurvivalState {
    IN_GAME= 1,
    PAUSE= 2,
};


class Survival : public Modality  {
    private:
        DrawManager* drawer;
        Player player;
        SurvivalState state;
        Texture2D* mapTexture;
    public:
        Survival();
        ~Survival() override;

        void drawModality() override;
        void drawEndModality() override;
        ControllerExitCode handleModality() override;
};

#endif
