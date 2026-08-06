#ifndef CREDITS_HPP
#define CREDITS_HPP

// #include "../../../../core/modality.hpp"
// #include "../../../../core/system.hpp"
#include "../../../../core/draw_manager.hpp"
#include "../../../../core/game_manager.hpp"
#include <raylib.h>

class Credits : public Modality {
    private:
        static const int AUTOSCROLL_SPEED = 80, CREDITS_HEIGHT_END = 1100;
        float shiftDown;
        bool endedAutoScrool;

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
