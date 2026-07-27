#include "../../core/draw_manager.hpp"
#include "../../core/sound_manager.hpp"
#include "../../core/system.hpp"

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

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

class Settings{
    private:
        System* sys= System::getInstance();
        DrawManager* drawer= DrawManager::getInstance();
        SoundManager* soundMan= SoundManager::getInstance();
        SettingSelection choice;
    public:
        void drawSettings();
        void handleSettings();
        bool shouldExit();
};


#endif
