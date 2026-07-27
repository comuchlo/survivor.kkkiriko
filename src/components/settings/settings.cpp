#include <raylib.h>
#include "settings.hpp"

SettingSelection& operator++(SettingSelection& val){
    if (val == SettingSelection::EXIT){
        val = SettingSelection::MASTERVOLUME;
    }else{
        val = static_cast<SettingSelection>(
            static_cast<int>(val) + 1
        );
    }
    return val;
}

SettingSelection operator++(SettingSelection& val, int)
{
  SettingSelection oldVal = val;
  ++val; //reuse the preincrement implementation
  return oldVal;
}

SettingSelection& operator--(SettingSelection& val){
    if (val == SettingSelection::MASTERVOLUME){
        val = SettingSelection::EXIT;
    }else{
        val = static_cast<SettingSelection>(
            static_cast<int>(val) - 1
        );
    }
    return val;
}

SettingSelection operator--(SettingSelection& val, int)
{
  SettingSelection oldVal = val;
  --val; //reuse the predecrement implementation
  return oldVal;
}

bool Settings::shouldExit(){
    return (this->choice == SettingSelection::EXIT);
}
