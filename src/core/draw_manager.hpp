#include <raylib.h>
#include "system.hpp"

#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H


class DrawManager {
    private:
        static DrawManager* instance;
        RenderTexture2D idealScreen;
        DrawManager();
    public:
        ~DrawManager();
        DrawManager(const DrawManager&) = delete;
        DrawManager& operator=(const DrawManager&) = delete;
        static DrawManager* getInstance();

        System* sys= System::getInstance();

        void drawRangeBar(int progress, int height);
        void drawTextSF(const char *text, int x, int y, int font, Color col1, Color col2, Color col3);
        void drawArrowSF(float x, float y, float width, float height, float thick, bool verse, Color col1, Color col2, Color col3);
};


#endif
