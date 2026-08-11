#ifndef CREDITS_HPP
#define CREDITS_HPP

#include "../../../../core/draw_manager.hpp"
#include "../../../../core/game_manager.hpp"

class Credits : public Modality {
    private:
        static const int DEF_AUTOSCROLL_SPEED = 80, MAX_AUTOSCROLL_SPEED = 320,
            CREDITS_HEIGHT_END = 1100;
        int autoscroll_speed;
        bool endedAutoScrool, stoppedLastText;

        System* sys;
        DrawManager* drawer;
        GameManager* game_manager;
        Texture2D* backgroundImage; //shared from parent

    public:
        Credits(Texture2D* backgroundImage);
        ~Credits() override;

        // inherited methods to override
        void drawModality() override;
        // void drawEndModality() override;
        ControllerExitCode handleModality() override;
};


#endif
