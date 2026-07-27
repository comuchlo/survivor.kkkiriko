#include <raylib.h>
#include "settings.hpp"


void Settings::handleSettings() {
    //events
	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
	    this->choice--;
        this->soundMan->playCurrent();
	}

	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
	    this->choice++;
        this->soundMan->playCurrent();
	}

	if  ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && this->choice <= SettingSelection::EFFECTSVOLUME) {//right
        switch (this->choice) {
            case SettingSelection::MASTERVOLUME:
                this->soundMan->incrementGlobalVolume();
                break;
            case SettingSelection::MUSICVOLUME:
                this->soundMan->incrementMusicVolume();
                break;
            case SettingSelection::EFFECTSVOLUME:
                this->soundMan->incrementSfxVolume();
                break;
            default:
                break;
        }
	}

	if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && this->choice <= SettingSelection::EFFECTSVOLUME) {//left
        switch (this->choice) {
            case SettingSelection::MASTERVOLUME:
                this->soundMan->decrementGlobalVolume();
                break;
            case SettingSelection::MUSICVOLUME:
                this->soundMan->decrementMusicVolume();
                break;
            case SettingSelection::EFFECTSVOLUME:
                this->soundMan->decrementSfxVolume();
                break;
            default:
                break;
        }
	}

	if (IsKeyPressed(KEY_ENTER) && this->choice == SettingSelection::RESET)  {//enter
	    this->soundMan->resetVolume();

		/* } else if (*choice == 40 + settingsOpt) {//exit
			*choice = pause;//back to prew/paused choice
		} */
	}
}
