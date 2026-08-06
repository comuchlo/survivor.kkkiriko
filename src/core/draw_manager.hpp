#ifndef DRAW_MANAGER_HPP // zio pera
#define DRAW_MANAGER_HPP

// includes also "soundmanager.hpp" { <raylib.h> }, "modality.hpp"
#include "system.hpp"
#include <memory>

class DrawManager {
    private:
        static DrawManager* instance;
        System* sys;
        DrawManager();

    public:
        ~DrawManager();
        DrawManager(const DrawManager&) = delete;
        DrawManager& operator=(const DrawManager&) = delete;
        static DrawManager* getInstance();

        // N.B.: every draw calls should refer to render width & height
        void drawRangeBar(int progress, int height);
        void drawTextSF(const char *text, int x, int y, int font, Color col1, Color col2, Color col3);
        void drawArrowSF(float x, float y, float width, float height, float thick, bool verse, Color col1, Color col2, Color col3);
};


#endif
