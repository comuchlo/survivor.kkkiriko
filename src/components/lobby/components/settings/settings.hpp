#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "../../lobby.hpp"
#include <raylib.h>

enum class SettingSelection {
    MASTERVOLUME= 1,
    MUSICVOLUME= 2,
    EFFECTSVOLUME= 3,
    RESETAUDIO= 4,
    DISPLAYMODE = 5,
    RESOLUTION = 6,
    FPS = 7,
    VSYNC = 8,
    RESETVIDEO = 9,
    EXIT= 10,
};

SettingSelection& operator++(SettingSelection& val);
SettingSelection  operator++(SettingSelection& val, int);

SettingSelection& operator--(SettingSelection& val);
SettingSelection  operator--(SettingSelection& val, int);

class Settings : public LobbyScreen {
    private:
        SettingSelection choice;
    public:
        Settings();
        ~Settings() override = default;
        void drawModality() override;
        LobbyState handleLobbySubMode() override;

};

#endif
