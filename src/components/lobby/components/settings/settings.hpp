#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "../../../../core/draw_manager.hpp"
#include <raylib.h>

enum class SettingSelection {
    MASTERVOLUME= 1,
    MUSICVOLUME= 2,
    EFFECTSVOLUME= 3,
    RESETAUDIO= 4,
    DISPLAYMODE = 5,
    RESOLUTION = 6,
    RESETVIDEO = 7,
    EXIT= 8,
};

SettingSelection& operator++(SettingSelection& val);
SettingSelection  operator++(SettingSelection& val, int);

SettingSelection& operator--(SettingSelection& val);
SettingSelection  operator--(SettingSelection& val, int);

DisplayMode& operator++(DisplayMode& val);
DisplayMode  operator++(DisplayMode& val, int);

DisplayMode& operator--(DisplayMode& val);
DisplayMode  operator--(DisplayMode& val, int);

class Settings : public Modality {
    private:
        System* sys;
        DrawManager* drawer;
        SettingSelection choice;
        Texture2D* backgroundImage;
    public:
        Settings(Texture2D* backgroundImage);
        ~Settings() override;
        void drawModality() override;
        ControllerExitCode handleModality() override;
};

#endif
