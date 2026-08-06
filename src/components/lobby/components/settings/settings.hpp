#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "../../../../core/draw_manager.hpp"
#include <raylib.h>

enum class SettingSelection {
    MASTERVOLUME= 1,
    MUSICVOLUME= 2,
    EFFECTSVOLUME= 3,
    RESET= 4,
    EXIT= 5,
};

SettingSelection& operator++(SettingSelection& val);
SettingSelection  operator++(SettingSelection& val, int);

SettingSelection& operator--(SettingSelection& val);
SettingSelection  operator--(SettingSelection& val, int);

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
