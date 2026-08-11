#include "settings.hpp"
#include <raylib.h>

SettingSelection& operator++(SettingSelection& val) {
    if (val == SettingSelection::EXIT){
        val = SettingSelection::MASTERVOLUME;
    }else{
        val = static_cast<SettingSelection>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

SettingSelection operator++(SettingSelection& val, int) {
  SettingSelection oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

SettingSelection& operator--(SettingSelection& val) {
    if (val == SettingSelection::MASTERVOLUME){
        val = SettingSelection::EXIT;
    }else{
        val = static_cast<SettingSelection>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

SettingSelection operator--(SettingSelection& val, int) {
  SettingSelection oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}

DisplayMode& operator++(DisplayMode& val) {
    if (val == DisplayMode::BORDERLESS_WINDOW){
        val = DisplayMode::RESIZABLE_WINDOW;
    }else{
        val = static_cast<DisplayMode>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

DisplayMode operator++(DisplayMode& val, int) {
  DisplayMode oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

DisplayMode& operator--(DisplayMode& val) {
    if (val == DisplayMode::RESIZABLE_WINDOW){
        val = DisplayMode::BORDERLESS_WINDOW;
    }else{
        val = static_cast<DisplayMode>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

DisplayMode operator--(DisplayMode& val, int) {
  DisplayMode oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}

Settings::Settings(Texture2D* backgroundImage) {
    sys = System::getInstance();
    drawer = DrawManager::getInstance();
    this->backgroundImage = backgroundImage;
    choice = SettingSelection::MASTERVOLUME;
}

Settings::~Settings() {

}
