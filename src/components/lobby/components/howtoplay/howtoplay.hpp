#ifndef HOWTOPLAY_HPP
#define HOWTOPLAY_HPP

#include "../../../../core/draw_manager.hpp"
#include "../../../../core/game_manager.hpp"

class HowToPlay : public Modality {
    private:
        System* sys;
        DrawManager* drawer;
        GameManager* game_manager;
        Texture2D* backgroundImage; //shared from parent

    public:
        HowToPlay(Texture2D* backgroundImage);
        ~HowToPlay() override;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        ControllerExitCode handleModality() override;
};


#endif
